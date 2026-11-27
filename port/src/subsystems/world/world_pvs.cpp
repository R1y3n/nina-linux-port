#include "world_pvs.h"
#include "world_renderer.h"
#include "world_tree_abi.h"
#include "subsystems/renderer/fog_state.h"
#include "utils/log.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <unordered_set>

namespace
{
    static WorldPVSState &PVSState() { return WorldPVS::Instance().State(); }

    static std::string HexVisPrefix(const uint8 *p, uint32 size, uint32 maxBytes)
    {
        if (!p || !size)
            return "(empty)";
        std::ostringstream ss;
        const uint32 n = std::min(size, maxBytes);
        ss << std::hex << std::setfill('0');
        for (uint32 i = 0; i < n; ++i)
        {
            if (i)
                ss << ' ';
            ss << std::setw(2) << static_cast<unsigned>(p[i]);
        }
        if (size > n)
            ss << " ...";
        return ss.str();
    }

    // This mirrors the D3D11 renderer's QOM_VisQueryEx path instead of trying to
    // reverse/decode WorldBsp::m_pVisListData ourselves.
    struct UserPortalVisCompat
    {
        char *m_szName;     // +0
        uint16 m_wData4;    // +4
        uint16 m_wData6;    // +6
        uint16 m_wPortalID; // +8
        uint16 m_wData10;   // +10
        LTVector m_vCenter; // +12
        LTVector m_vDims;   // +24
    };
    static_assert(offsetof(UserPortalVisCompat, m_vCenter) == 12, "UserPortal center offset mismatch");
    static_assert(offsetof(UserPortalVisCompat, m_vDims) == 24, "UserPortal dims offset mismatch");

    struct WorldTreeNodeVisCompat
    {
        uint8 m_objectLinks[24]; // +0, CheapLTLink[3]
        LTVector m_vBBoxMin;     // +24
        LTVector m_vBBoxMax;     // +36
        LTVector m_vCenter;      // +48
        float m_fMinSize;        // +60
        float m_fRadius;         // +64
    };
    static_assert(offsetof(WorldTreeNodeVisCompat, m_vCenter) == 48, "WorldTreeNode center offset mismatch");
    static_assert(offsetof(WorldTreeNodeVisCompat, m_fRadius) == 64, "WorldTreeNode radius offset mismatch");

    struct PVSQuat
    {
        float x, y, z, w;
    };

    static PVSQuat PVS_NormalizeQuat(PVSQuat q)
    {
        const float d = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
        if (d <= 1.0e-8f)
            return {0, 0, 0, 1};
        return {q.x / d, q.y / d, q.z / d, q.w / d};
    }

    static LTVector PVS_Rotate(PVSQuat q, const LTVector &v)
    {
        q = PVS_NormalizeQuat(q);
        const LTVector u{q.x, q.y, q.z};
        const float dotUV = u.x * v.x + u.y * v.y + u.z * v.z;
        const float dotUU = u.x * u.x + u.y * u.y + u.z * u.z;
        const LTVector cross{
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x};
        return {
            u.x * (2.0f * dotUV) + v.x * (q.w * q.w - dotUU) + cross.x * (2.0f * q.w),
            u.y * (2.0f * dotUV) + v.y * (q.w * q.w - dotUU) + cross.y * (2.0f * q.w),
            u.z * (2.0f * dotUV) + v.z * (q.w * q.w - dotUU) + cross.z * (2.0f * q.w)};
    }

    struct EnginePVSContext
    {
        WorldBspCompat *visBsp = nullptr;
        LTVector camera{};
        PVSQuat invCameraQuat{0, 0, 0, 1};
        float tanHalfFovX = 1.0f;
        float tanHalfFovY = 1.0f;
        float nearZ = 1.0f;
        float farZ = 10000.0f;
        uint32 portalTests = 0;
        uint32 portalRejected = 0;
        uint32 nodeTests = 0;
        uint32 nodeRejected = 0;
        std::vector<uint32> leaves;
        uint32 objectCallbacks = 0;
        uint32 leafPolyRefs = 0;
        std::unordered_set<WorldPolyCompat *> visiblePolys;
        std::vector<WorldModelInstanceCompat *> visibleWorldModels;
        std::vector<ModelInstanceCompat *> visibleModels;
        std::vector<DynamicLightCompat *> visibleDynamicLights;
        std::vector<SpriteInstanceCompat *> visibleSprites;
        std::vector<ParticleSystemCompat *> visibleParticleSystems;
        std::vector<PolyGridCompat *> visiblePolyGrids;
        std::vector<LineSystemCompat *> visibleLineSystems;
        std::vector<CanvasCompat *> visibleCanvases;
        std::unordered_set<LTObjectCompat *> seenObjects;
        // Objects AddObjects put in LT's vis buffer. ObjectCB
        // can see survivors of the clip and skip 0x400 rejection.
        std::unordered_set<LTObjectCompat *> bufferedObjects;
        // Stock d3d.ren uses LTObject::m_dwWTFrameCode while recursively walking
        // attachment chains.  Keep a separate traversal set so rejected children
        // can still expose their own descendants without creating attachment loops.
        std::unordered_set<LTObjectCompat *> attachmentTraversalSeen;
    };

    static EnginePVSContext *g_enginePVSContext = nullptr;

    // Client impact marks in Talon are ordinary OT_SPRITE objects.  The classic
    // MarkSFX construction is VISIBLE | NOLIGHT | ROTATEABLESPRITE (0x209), with
    // an optional SPRITEBIAS bit depending on the game/effect.  Keep this helper
    // deliberately narrow so the AddObjects compatibility path below cannot
    // change ordinary billboard visibility behavior.
    static bool EnginePVS_IsSurfaceMarkSprite(const LTObjectCompat *obj)
    {
        if (!obj || obj->m_nObjectType != OT_SPRITE)
            return false;
        constexpr uint32 kRequired = FLAG_VISIBLE | FLAG_NOLIGHT | FLAG_ROTATEABLESPRITE;
        return (obj->m_dwFlags & kRequired) == kRequired;
    }

    static bool EnginePVS_AddResolvedObject(EnginePVSContext *ctx, LTObjectCompat *obj, bool rejectInternal)
    {
        if (!ctx || !obj)
            return false;

        // IMPORTANT: do not mark an object as seen until AFTER the stock root-only
        // rejection tests have passed.  d3d.ren can encounter an attached
        // object once as a WorldTree root (where internal 0x400 rejects it), then
        // later resolve the same object through its parent's attachment list.  The
        // attachment path deliberately does NOT repeat the root-only 0x400 test.
        //
        // The previous implementation inserted into seenObjects before testing
        // internal flags.  That made the later attachment submission look like a
        // duplicate and silently discarded it -- exactly the opposite of stock.

        // Root ObjectCB in d3d.ren rejects internal bit 0x400.  Attached
        // children are handled by the attachment sub-loop after ProcessAttachment
        // and do not repeat that root-only rejection.
        if (rejectInternal && (obj->m_dwInternalFlags & 0x400u))
        {
            if (LogIsSessionEnabled() && EnginePVS_IsSurfaceMarkSprite(obj))
            {
                static uint32 markInternalBudget = 64;
                if (LogIsSessionEnabled() && (markInternalBudget))
                {
                    --markInternalBudget;
                    LOG_SESSION("World3D PVS-DECAL REJECT internal obj=%p flags=%08X flags2=%08X internal=%08X srv=%p pos=(%.2f %.2f %.2f)",
                                obj, obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags, obj->m_pSrvObjData,
                                obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
                }
            }
            static int internalSkipBudget = 32;
            if (LogIsSessionEnabled() && ((internalSkipBudget > 0 && internalSkipBudget--) && obj->m_nObjectType == OT_MODEL))
                LOG_SESSION("World3D MODEL INTERNAL-SKIP obj=%p flags=%08X internal=%08X pos=(%.2f %.2f %.2f)",
                            obj, obj->m_dwFlags, obj->m_dwInternalFlags,
                            obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
            return false;
        }

        // d3d.ren rejects type 7 (PolyGrid) from the generic renderer
        // handler table, but it does NOT discard PolyGrids.  They are routed to
        // the dedicated VS_POLYGRIDS / VS_POLYGRIDS_TRANSLUCENT visible sets.
        // Our renderer has one unified PVS result, so emulate that side route
        // here instead of returning and losing the object entirely.
        if (obj->m_dwFlags2 & 0x100u)
            return false;

        const bool visible = (obj->m_dwFlags & FLAG_VISIBLE) != 0;
        const bool portalVisible = (obj->m_dwFlags & 0x400u) != 0;

        // Flags2 bit 0 is type-specific.  On ordinary render objects Talon's
        // WorldTree callback uses it as the portal-suppression state, but on
        // OT_LIGHT it is FLAG2_FORCEDYNAMICLIGHTWORLD.  Treating every bit-0
        // object as portal-suppressed silently rejected exactly the client lights
        // used for flashlights and other forced world-light FX.
        const bool portalSuppressed = (obj->m_nObjectType != OT_LIGHT) &&
                                      ((obj->m_dwFlags2 & 0x1u) != 0);
        if (!((visible && !portalSuppressed) || (!visible && portalVisible)))
        {
            if (LogIsSessionEnabled() && EnginePVS_IsSurfaceMarkSprite(obj))
            {
                static uint32 markVisRejectBudget = 64;
                if (LogIsSessionEnabled() && (markVisRejectBudget))
                {
                    --markVisRejectBudget;
                    LOG_SESSION("World3D PVS-DECAL REJECT visibility obj=%p visible=%u portalVisible=%u portalSuppressed=%u flags=%08X flags2=%08X internal=%08X",
                                obj, visible ? 1u : 0u, portalVisible ? 1u : 0u, portalSuppressed ? 1u : 0u,
                                obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags);
                }
            }
            return false;
        }

        // PolyGrid has a dedicated visibility bucket in d3d.ren.  The retail
        // generic ObjectCB excludes OT_POLYGRID because a separate handler owns
        // it; reproducing only that exclusion in OpenGL was why PolyGrids never
        // reached FXRenderer.
        if (obj->m_nObjectType == OT_POLYGRID)
        {
            if (!ctx->seenObjects.insert(obj).second)
                return false;
            auto *pg = reinterpret_cast<PolyGridCompat *>(obj);
            ctx->visiblePolyGrids.push_back(pg);
            static int pgAcceptBudget = 96;
            if (LogIsSessionEnabled() && ((pgAcceptBudget > 0 && pgAcceptBudget--)))
                LOG_SESSION("World3D POLYGRID PVS-ACCEPT obj=%p size=%ux%u data=%p indices=%p indexCount=%u tris=%u alpha=%u flags=%08X flags2=%08X",
                            pg, pg->m_dwWidth, pg->m_dwHeight, pg->m_pData, pg->m_pIndices,
                            pg->m_dwIndices, pg->m_dwTris, unsigned(pg->m_Base.m_nColorA),
                            pg->m_Base.m_dwFlags, pg->m_Base.m_dwFlags2);
            return true;
        }

        // Only accepted objects participate in our duplicate suppression.  This
        // mirrors d3d.ren's effective behavior: a root rejected before dispatch
        // must remain eligible to be resolved and dispatched as an attachment.
        if (!ctx->seenObjects.insert(obj).second)
            return false;

        switch (obj->m_nObjectType)
        {
        case OT_MODEL:
            ctx->visibleModels.push_back(reinterpret_cast<ModelInstanceCompat *>(obj));
            break;
        case OT_LIGHT:
        {
            auto *light = reinterpret_cast<DynamicLightCompat *>(obj);
            ctx->visibleDynamicLights.push_back(light);
            static uint32 lightAcceptBudget = 64;
            if (LogIsSessionEnabled() && (lightAcceptBudget))
            {
                --lightAcceptBudget;
                LOG_SESSION("World3D OT_LIGHT ACCEPT obj=%p pos=(%.2f %.2f %.2f) radius=%.2f rgb=(%u,%u,%u) flags=%08X flags2=%08X forcedWorld=%d onlyWorld=%d onlyObjects=%d",
                            light, light->m_Base.m_vPos.x, light->m_Base.m_vPos.y, light->m_Base.m_vPos.z,
                            light->m_fLightRadius, unsigned(light->m_Base.m_nColorR),
                            unsigned(light->m_Base.m_nColorG), unsigned(light->m_Base.m_nColorB),
                            light->m_Base.m_dwFlags, light->m_Base.m_dwFlags2,
                            (light->m_Base.m_dwFlags2 & FLAG2_FORCEDYNAMICLIGHTWORLD) ? 1 : 0,
                            (light->m_Base.m_dwFlags & FLAG_ONLYLIGHTWORLD) ? 1 : 0,
                            (light->m_Base.m_dwFlags & FLAG_ONLYLIGHTOBJECTS) ? 1 : 0);
            }
            break;
        }
        case OT_SPRITE:
            ctx->visibleSprites.push_back(reinterpret_cast<SpriteInstanceCompat *>(obj));
            if (LogIsSessionEnabled() && EnginePVS_IsSurfaceMarkSprite(obj))
            {
                static uint32 markAcceptBudget = 96;
                if (LogIsSessionEnabled() && (markAcceptBudget))
                {
                    --markAcceptBudget;
                    auto *sp = reinterpret_cast<SpriteInstanceCompat *>(obj);
                    LOG_SESSION("World3D PVS-DECAL ACCEPT obj=%p flags=%08X flags2=%08X internal=%08X srv=%p hpoly=%08X pos=(%.2f %.2f %.2f) scale=(%.4f %.4f %.4f)",
                                obj, obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags, obj->m_pSrvObjData,
                                sp->m_hClipperPoly, obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z,
                                obj->m_vScale.x, obj->m_vScale.y, obj->m_vScale.z);
                }
            }
            break;
        case OT_PARTICLESYSTEM:
            ctx->visibleParticleSystems.push_back(reinterpret_cast<ParticleSystemCompat *>(obj));
            break;
        case OT_LINESYSTEM:
            // d3d.ren handler 0x10023CE0 submits OT_LINESYSTEM to the
            // VisibleSet list later queued by 0x10023D30.
            ctx->visibleLineSystems.push_back(reinterpret_cast<LineSystemCompat *>(obj));
            break;
        case OT_CANVAS:
            // d3d.ren 0x10022A9F submits every Canvas to its visible set.
            // 0x10022B50 later splits bit 0x10 of client flags into solid
            // versus sorted-translucent Canvas passes.
            ctx->visibleCanvases.push_back(reinterpret_cast<CanvasCompat *>(obj));
            break;
        case OT_WORLDMODEL:
        case OT_CONTAINER:
        {
            auto *wm = reinterpret_cast<WorldModelInstanceCompat *>(obj);
            if (wm->m_pOriginalBsp)
                ctx->visibleWorldModels.push_back(wm);
            break;
        }
        default:
            break;
        }
        return true;
    }

    static void EnginePVS_ProcessAttachmentsRecursive(EnginePVSContext *ctx, LTObjectCompat *parent, uint32 depth)
    {
        // d3d.ren 0x10039440 caps attachment recursion at depth 32.
        RenderStruct *rs = WorldRenderer::Instance().GetRenderStruct();
        if (!ctx || !parent || depth > 32u || !parent->m_pAttachments ||
            !rs || !rs->ProcessAttachment)
            return;

        uint32 attachGuard = 0;
        for (Attachment *a = parent->m_pAttachments; a && attachGuard++ < 4096; a = a->m_pNext)
        {
            LTObject *childRaw = rs->ProcessAttachment(
                reinterpret_cast<LTObject *>(parent), a);
            auto *child = reinterpret_cast<LTObjectCompat *>(childRaw);
            if (!child)
                continue;

            // Stock checks the child's WT frame code before recursing.  A local
            // traversal set gives us the same per-query cycle/duplicate protection
            // without falsely treating a root rejected by internal 0x400 as
            // already rendered.
            if (!ctx->attachmentTraversalSeen.insert(child).second)
                continue;

            // Exact stock order: recurse into the child's attachments first, then
            // test/dispatch the child itself.  This matters when an intermediate
            // attachment node is not renderer-eligible but owns a visible model.
            EnginePVS_ProcessAttachmentsRecursive(ctx, child, depth + 1u);

            const bool added = EnginePVS_AddResolvedObject(ctx, child, false);
            static int attachBudget = 192;
            if (LogIsSessionEnabled() && ((attachBudget > 0 && attachBudget--)))
            {
                const char *childName = "";
                if (child->m_nObjectType == OT_MODEL)
                {
                    auto *childInst = reinterpret_cast<ModelInstanceCompat *>(child);
                    Model *childModel = GetModelFromInstance(childInst);
                    if (childModel && childModel->m_szFilename)
                        childName = childModel->m_szFilename;
                }
                LOG_SESSION("World3D PVS-ATTACH depth=%u parent=%p child=%p type=%u added=%u model='%s' flags=%08X flags2=%08X internal=%08X pos=(%.2f %.2f %.2f)",
                            depth, parent, child, unsigned(child->m_nObjectType), added ? 1u : 0u, childName,
                            child->m_dwFlags, child->m_dwFlags2, child->m_dwInternalFlags,
                            child->m_vPos.x, child->m_vPos.y, child->m_vPos.z);
            }
        }
    }

    static void __cdecl EnginePVS_ObjectCB(void *pObj, void *)
    {
        EnginePVSContext *ctx = g_enginePVSContext;
        if (!ctx || !pObj)
            return;
        ++ctx->objectCallbacks;

        auto *obj = reinterpret_cast<LTObjectCompat *>(pObj);

        if (LogIsSessionEnabled() && EnginePVS_IsSurfaceMarkSprite(obj))
        {
            static uint32 rawMarkBudget = 96;
            if (LogIsSessionEnabled() && (rawMarkBudget))
            {
                --rawMarkBudget;
                auto *sp = reinterpret_cast<SpriteInstanceCompat *>(obj);
                LOG_SESSION("World3D PVS-DECAL RAW-CB obj=%p flags=%08X flags2=%08X internal=%08X srv=%p hpoly=%08X wt=%08X pos=(%.2f %.2f %.2f)",
                            obj, obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags, obj->m_pSrvObjData,
                            sp->m_hClipperPoly, obj->m_dwWTFrameCode, obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
            }
        }

        // Targeted diagnostic: log a dropship at the raw WorldTree callback
        // boundary, before any renderer-side eligibility/deduplication.
        if (LogIsSessionEnabled() && obj->m_nObjectType == OT_MODEL)
        {
            auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
            Model *model = GetModelFromInstance(inst);
            const char *name = (model && model->m_szFilename) ? model->m_szFilename : "";
            if (strstr(name, "dropship") || strstr(name, "Dropship") || strstr(name, "DROPSHIP"))
            {
                static int rawDropBudget = 96;
                if (LogIsSessionEnabled() && ((rawDropBudget > 0 && rawDropBudget--)))
                    LOG_SESSION("World3D PVS-RAW DROPSHIP obj=%p model='%s' flags=%08X flags2=%08X internal=%08X attach=%p pos=(%.2f %.2f %.2f)",
                                obj, name, obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags, obj->m_pAttachments,
                                obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
            }
        }

        // Objects from the AddObjects buffer keep that path's exemption from the
        // root-only internal 0x400 rejection.
        const bool buffered = ctx->bufferedObjects.find(obj) != ctx->bufferedObjects.end();
        if (!EnginePVS_AddResolvedObject(ctx, obj, !buffered))
            return;

        // Stock ObjectCB 0x10039900 enters the recursive attachment walker only
        // after the root has passed its renderer eligibility tests and handler.
        EnginePVS_ProcessAttachmentsRecursive(ctx, obj, 1u);
    }

    static void __cdecl EnginePVS_AddObjects(LTLinkCompat *pLink,
                                             LTObjectCompat ***pppBuffer,
                                             uint32 *pCounter)
    {
        if (!pLink || !pppBuffer || !*pppBuffer || !pCounter)
            return;

        // IMPORTANT:
        // - walk m_pNext, not m_pPrev
        // - reject m_pSrvObjData != nullptr (+0x190)
        // - do NOT reject internal 0x400 here; the normal ObjectCB owns that test
        // - apply the same in-world visibility/portal eligibility used by d3d.ren
        auto *cur = reinterpret_cast<LTLinkCompat *>(pLink->m_pNext);
        uint32 guard = 0;

        while (cur && cur != pLink && guard++ < 65536)
        {
            auto *obj = reinterpret_cast<LTObjectCompat *>(cur->m_pData);

            // A server-backed object is not a renderer-owned client object for
            // this AddObjects pass. Skip this entry, but DO NOT terminate the
            // entire list walk. M3.14.5 returned here and starved every object
            // appearing after the first server-backed WorldModel, collapsing both
            // ABC and WorldModel visibility sets.
            if (obj && obj->m_pSrvObjData != nullptr)
            {
                static int srvSkipBudget = 64;
                if (LogIsSessionEnabled() && ((srvSkipBudget > 0 && srvSkipBudget--)))
                    LOG_SESSION("World3D ADDOBJECTS SRV-SKIP obj=%p type=%u srv=%p flags=%08X internal=%08X",
                                obj, static_cast<unsigned>(obj->m_nObjectType), obj->m_pSrvObjData,
                                obj->m_dwFlags, obj->m_dwInternalFlags);

                cur = reinterpret_cast<LTLinkCompat *>(cur->m_pNext);
                continue;
            }

            if (obj)
            {
                const uint32 type = obj->m_nObjectType;

                // PolyGrid is excluded from d3d.ren's *generic* handler table,
                // but is inserted into dedicated PolyGrid visible sets.  Our
                // unified visible result needs to retain it here.
                const bool processable = type < 11;

                const bool sky = (obj->m_dwFlags2 & 0x100u) != 0;
                const bool visible = (obj->m_dwFlags & FLAG_VISIBLE) != 0;
                const bool portalVisible = (obj->m_dwFlags & 0x400u) != 0;
                const bool portalSuppressed = (type != OT_LIGHT) && ((obj->m_dwFlags2 & 0x1u) != 0);

                if (processable && !sky &&
                    ((visible && !portalSuppressed) ||
                     (!visible && portalVisible)))
                {
                    // d3d.ren 0x10039A40 places these client-side objects into
                    // DoVisQuery's object buffer without the root-only
                    // internal-0x400 rejection from ObjectCB 0x10039900.
                    //
                    // Don't add them to the visible sets here.
                    // LT's vq_VisitNode (0x0049E8D0) collects this buffer at
                    // each node it walks and clips it against each node plane
                    // on its way down. LT then passes the 'survivors' to
                    // ObjectCB at a visible leaf.
                    // Adding them to visible sets here skipped the engine's clip.
                    // Just 'remember' the object so ObjectCB admits it with
                    // rejectInternal=false. m_open's TranslucentWorldModel8 arrives
                    // this way and still needs that exemption.
                    if (g_enginePVSContext)
                    {
                        const bool wasBuffered =
                            !g_enginePVSContext->bufferedObjects.insert(obj).second;

                        static uint32 addObjectsBudget = 192;
                        if (LogIsSessionEnabled() && (addObjectsBudget && !wasBuffered))
                        {
                            --addObjectsBudget;
                            const char *name = "";
                            if (obj->m_nObjectType == OT_WORLDMODEL ||
                                obj->m_nObjectType == OT_CONTAINER)
                            {
                                auto *wm = reinterpret_cast<WorldModelInstanceCompat *>(obj);
                                if (wm->m_pOriginalBsp)
                                    name = wm->m_pOriginalBsp->m_szWorldName;
                            }
                            else if (obj->m_nObjectType == OT_MODEL)
                            {
                                auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
                                Model *model = GetModelFromInstance(inst);
                                if (model && model->m_szFilename)
                                    name = model->m_szFilename;
                            }

                            LOG_SESSION("World3D ADDOBJECTS BUFFER obj=%p type=%u name='%s' flags=%08X flags2=%08X internal=%08X srv=%p pos=(%.2f %.2f %.2f)",
                                        obj, unsigned(obj->m_nObjectType), name,
                                        obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags,
                                        obj->m_pSrvObjData, obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
                        }

                        if (LogIsSessionEnabled() && EnginePVS_IsSurfaceMarkSprite(obj))
                        {
                            static uint32 markAddObjectsBudget = 128;
                            if (LogIsSessionEnabled() && (markAddObjectsBudget && !wasBuffered))
                            {
                                --markAddObjectsBudget;
                                auto *sp = reinterpret_cast<SpriteInstanceCompat *>(obj);
                                LOG_SESSION("World3D PVS-DECAL ADDOBJECTS obj=%p flags=%08X flags2=%08X internal=%08X srv=%p hpoly=%08X",
                                            obj, obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags,
                                            obj->m_pSrvObjData, sp->m_hClipperPoly);
                            }
                        }
                    }

                    (*pppBuffer)[*pCounter] = obj;
                    ++(*pCounter);
                }
            }

            cur = reinterpret_cast<LTLinkCompat *>(cur->m_pNext);
        }
    }

    static void __cdecl EnginePVS_LeafCB(LeafCompat *leaf, void *)
    {
        EnginePVSContext *ctx = g_enginePVSContext;
        if (!ctx || !ctx->visBsp || !leaf || !ctx->visBsp->m_pLeafs)
            return;

        if (leaf < ctx->visBsp->m_pLeafs ||
            leaf >= ctx->visBsp->m_pLeafs + ctx->visBsp->m_dwLeafs)
            return;

        const uint32 index = static_cast<uint32>(leaf - ctx->visBsp->m_pLeafs);
        ctx->leaves.push_back(index);

        // Original d3d.ren leaf callback 0x10039AE0 iterates exactly these:
        //   Leaf::m_pPolies (+32), Leaf::m_dwPolies (+36)
        // and uses WorldPoly::m_wFrameCode to suppress duplicates between leaves.
        // We use an unordered_set for the same per-frame de-duplication.
        if (leaf->m_pPolies && leaf->m_dwPolies > 0 && leaf->m_dwPolies < 65536)
        {
            ctx->leafPolyRefs += leaf->m_dwPolies;
            for (uint32 i = 0; i < leaf->m_dwPolies; ++i)
            {
                WorldPolyCompat *poly = leaf->m_pPolies[i];
                if (poly)
                    ctx->visiblePolys.insert(poly);
            }
        }
    }

    // Stock d3d.ren truth:
    //   0x1000F458 = UserPortal AABB against all six current clip planes.
    //   0x10039D90 = WorldTreeNode center/radius sphere against those planes.
    // The old OpenGL stubs returned true unconditionally, which let DoVisQuery
    // walk/admit WorldTree branches stock Talon rejects.
    static LTVector EnginePVS_ToCamera(const EnginePVSContext *ctx, const LTVector &p)
    {
        const LTVector rel{p.x - ctx->camera.x, p.y - ctx->camera.y, p.z - ctx->camera.z};
        return PVS_Rotate(ctx->invCameraQuat, rel);
    }

    static float EnginePVS_PlaneDistance(const EnginePVSContext *ctx, const LTVector &p, int plane)
    {
        // Camera space is +Z forward, matching this renderer's world/model shaders.
        // Side-plane equations are normalized so a WorldTree sphere radius can be
        // compared directly, exactly like d3d.ren's dot(center,n)-dist < -radius.
        switch (plane)
        {
        case 0:
        {
            const float inv = 1.0f / std::sqrt(1.0f + ctx->tanHalfFovX * ctx->tanHalfFovX);
            return (p.x + p.z * ctx->tanHalfFovX) * inv; // left
        }
        case 1:
        {
            const float inv = 1.0f / std::sqrt(1.0f + ctx->tanHalfFovX * ctx->tanHalfFovX);
            return (-p.x + p.z * ctx->tanHalfFovX) * inv; // right
        }
        case 2:
        {
            const float inv = 1.0f / std::sqrt(1.0f + ctx->tanHalfFovY * ctx->tanHalfFovY);
            return (p.y + p.z * ctx->tanHalfFovY) * inv; // bottom
        }
        case 3:
        {
            const float inv = 1.0f / std::sqrt(1.0f + ctx->tanHalfFovY * ctx->tanHalfFovY);
            return (-p.y + p.z * ctx->tanHalfFovY) * inv; // top
        }
        case 4:
            return p.z - ctx->nearZ; // near
        default:
            return ctx->farZ - p.z; // far
        }
    }

    static int32 __cdecl EnginePVS_PortalTest(void *pPortal)
    {
        EnginePVSContext *ctx = g_enginePVSContext;
        auto *portal = reinterpret_cast<UserPortalVisCompat *>(pPortal);
        if (!ctx || !portal)
            return 1;
        ++ctx->portalTests;

        LTVector corners[8];
        for (uint32 i = 0; i < 8; ++i)
        {
            const LTVector worldPt{
                portal->m_vCenter.x + ((i & 1) ? portal->m_vDims.x : -portal->m_vDims.x),
                portal->m_vCenter.y + ((i & 2) ? portal->m_vDims.y : -portal->m_vDims.y),
                portal->m_vCenter.z + ((i & 4) ? portal->m_vDims.z : -portal->m_vDims.z)};
            corners[i] = EnginePVS_ToCamera(ctx, worldPt);
        }

        for (int plane = 0; plane < 6; ++plane)
        {
            bool anyInFront = false;
            for (const LTVector &c : corners)
            {
                if (EnginePVS_PlaneDistance(ctx, c, plane) >= 0.0f)
                {
                    anyInFront = true;
                    break;
                }
            }
            if (!anyInFront)
            {
                ++ctx->portalRejected;
                return 0;
            }
        }
        return 1;
    }

    static int32 __cdecl EnginePVS_NodeFilter(void *pNode)
    {
        EnginePVSContext *ctx = g_enginePVSContext;
        auto *node = reinterpret_cast<WorldTreeNodeVisCompat *>(pNode);
        if (!ctx || !node)
            return 1;
        ++ctx->nodeTests;

        const LTVector center = EnginePVS_ToCamera(ctx, node->m_vCenter);
        const float radius = node->m_fRadius;
        for (int plane = 0; plane < 6; ++plane)
        {
            if (EnginePVS_PlaneDistance(ctx, center, plane) < -radius)
            {
                ++ctx->nodeRejected;
                return 0;
            }
        }
        return 1;
    }

    static uint64_t HashVisibleLeaves(const std::vector<uint32> &leaves)
    {
        uint64_t h = 1469598103934665603ull;
        for (uint32 v : leaves)
        {
            h ^= static_cast<uint64_t>(v);
            h *= 1099511628211ull;
        }
        return h;
    }

    static bool QueryEnginePVS(MainWorldCompat *world, WorldBspCompat *vis, SceneDesc *scene)
    {
        if (!world || !vis || !scene)
            return false;
        const LTVector &camera = scene->m_vPos;

        // MainWorld::m_WorldTree begins at +108 in the Talon ABI.
        auto *tree = reinterpret_cast<WorldTreeCompat *>(
            reinterpret_cast<uint8 *>(world) + 108);

        if (!tree || !tree->m_pVTable || !tree->m_pVTable->DoVisQuery)
        {
            static bool logged = false;
            if (LogIsSessionEnabled() && (!logged))
            {
                logged = true;
                LOG_SESSION("World3D ENGINE PVS unavailable tree=%p vtable=%p",
                            tree, tree ? tree->m_pVTable : nullptr);
            }
            return false;
        }

        EnginePVSContext ctx;
        ctx.visBsp = vis;
        ctx.camera = camera;
        // ToCamera uses the conjugate of the normalized camera quaternion.
        const PVSQuat q = PVS_NormalizeQuat({scene->m_rRotation.x, scene->m_rRotation.y,
                                             scene->m_rRotation.z, scene->m_rRotation.w});
        ctx.invCameraQuat = {-q.x, -q.y, -q.z, q.w};
        ctx.tanHalfFovX = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
        ctx.tanHalfFovY = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
        ctx.nearZ = 1.0f;
        ctx.farZ = std::max(2.0f, scene->m_fFarZ);
        ctx.leaves.reserve(vis->m_dwLeafs);

        VisQueryRequestCompat request{};
        request.m_eObjArray = NOA_Objects_Compat;
        request.m_vViewpoint = camera;

        // D3D11 renderer default: VisQueryViewRadius = 10000.
        request.m_fViewRadius = 10000.0f;
        request.m_ObjectCB = &EnginePVS_ObjectCB;
        request.m_AddObjects = &EnginePVS_AddObjects;
        request.m_pUserData = nullptr;
        request.m_LeafCB = &EnginePVS_LeafCB;
        request.m_PortalTest = &EnginePVS_PortalTest;
        request.m_NodeFilterFn = &EnginePVS_NodeFilter;
        request.m_vMin = {0, 0, 0};
        request.m_vMax = {0, 0, 0};
        request.m_pTree = nullptr;

        g_enginePVSContext = &ctx;
        tree->m_pVTable->DoVisQuery(tree, nullptr, &request);

        // WorldTree::AlwaysVisObjects is a visibility source of its own.  The
        // previous implementation only retained ReallyClose entries here, which
        // can drop ordinary cinematic models that Talon deliberately keeps on the
        // always-visible list.  Merge every eligible visible non-sky object and
        // dedupe it against DoVisQuery results.
        LTLinkCompat *head = &tree->m_AlwaysVisObjects;
        auto *cur = reinterpret_cast<LTLinkCompat *>(head->m_pNext);
        uint32 alwaysGuard = 0;
        uint32 alwaysAdded = 0;
        while (cur && cur != head && alwaysGuard++ < 65536)
        {
            auto *obj = reinterpret_cast<LTObjectCompat *>(cur->m_pData);
            if (obj && (obj->m_dwFlags & FLAG_VISIBLE) && !(obj->m_dwFlags2 & 0x100u))
            {
                bool added = false;
                if (obj->m_nObjectType == OT_MODEL)
                {
                    auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
                    if (std::find(ctx.visibleModels.begin(), ctx.visibleModels.end(), inst) == ctx.visibleModels.end())
                    {
                        ctx.visibleModels.push_back(inst);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_SPRITE)
                {
                    auto *sp = reinterpret_cast<SpriteInstanceCompat *>(obj);
                    if (std::find(ctx.visibleSprites.begin(), ctx.visibleSprites.end(), sp) == ctx.visibleSprites.end())
                    {
                        ctx.visibleSprites.push_back(sp);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_PARTICLESYSTEM)
                {
                    auto *ps = reinterpret_cast<ParticleSystemCompat *>(obj);
                    if (std::find(ctx.visibleParticleSystems.begin(), ctx.visibleParticleSystems.end(), ps) == ctx.visibleParticleSystems.end())
                    {
                        ctx.visibleParticleSystems.push_back(ps);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_POLYGRID)
                {
                    auto *pg = reinterpret_cast<PolyGridCompat *>(obj);
                    if (std::find(ctx.visiblePolyGrids.begin(), ctx.visiblePolyGrids.end(), pg) == ctx.visiblePolyGrids.end())
                    {
                        ctx.visiblePolyGrids.push_back(pg);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_LINESYSTEM)
                {
                    auto *ls = reinterpret_cast<LineSystemCompat *>(obj);
                    if (std::find(ctx.visibleLineSystems.begin(), ctx.visibleLineSystems.end(), ls) == ctx.visibleLineSystems.end())
                    {
                        ctx.visibleLineSystems.push_back(ls);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_CANVAS)
                {
                    auto *cv = reinterpret_cast<CanvasCompat *>(obj);
                    if (std::find(ctx.visibleCanvases.begin(), ctx.visibleCanvases.end(), cv) == ctx.visibleCanvases.end())
                    {
                        ctx.visibleCanvases.push_back(cv);
                        added = true;
                    }
                }
                else if (obj->m_nObjectType == OT_WORLDMODEL || obj->m_nObjectType == OT_CONTAINER)
                {
                    // WorldModels can live only on WorldTree::AlwaysVisObjects.
                    // This matters for cinematic translucent brushes (for example
                    // m_open's TranslucentWorldModel8/nebula layer): they need not
                    // be returned by the current leaf query, but stock Talon still
                    // submits them from the always-visible source.
                    auto *wm = reinterpret_cast<WorldModelInstanceCompat *>(obj);
                    if (wm->m_pOriginalBsp &&
                        std::find(ctx.visibleWorldModels.begin(), ctx.visibleWorldModels.end(), wm) == ctx.visibleWorldModels.end())
                    {
                        ctx.visibleWorldModels.push_back(wm);
                        added = true;
                    }
                }

                if (added)
                {
                    ++alwaysAdded;
                    static int alwaysBudget = 128;
                    if (LogIsSessionEnabled() && ((alwaysBudget > 0 && alwaysBudget--)))
                    {
                        const char *wmName = "";
                        if (obj->m_nObjectType == OT_WORLDMODEL || obj->m_nObjectType == OT_CONTAINER)
                        {
                            auto *wm = reinterpret_cast<WorldModelInstanceCompat *>(obj);
                            if (wm->m_pOriginalBsp)
                                wmName = wm->m_pOriginalBsp->m_szWorldName;
                        }
                        LOG_SESSION("World3D ALWAYS-ADD obj=%p type=%u name='%s' flags=%08X flags2=%08X internal=%08X srv=%p pos=(%.2f %.2f %.2f)",
                                    obj, unsigned(obj->m_nObjectType), wmName, obj->m_dwFlags, obj->m_dwFlags2,
                                    obj->m_dwInternalFlags, obj->m_pSrvObjData,
                                    obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z);
                    }
                }
            }
            cur = reinterpret_cast<LTLinkCompat *>(cur->m_pNext);
        }

        static uint32 lastAlwaysAdded = 0xFFFFFFFFu;
        if (LogIsSessionEnabled() && (lastAlwaysAdded != alwaysAdded))
        {
            lastAlwaysAdded = alwaysAdded;
            LOG_SESSION("World3D ALWAYS-ADD count=%u", alwaysAdded);
        }

        g_enginePVSContext = nullptr;

        // Keep the exact static polygon set returned through Talon's visible
        // leaf callback. This is the behavior used by the original d3d.ren.
        PVSState().visibleStaticPolys.swap(ctx.visiblePolys);
        PVSState().visibleLeafCount = static_cast<uint32>(ctx.leaves.size());
        PVSState().totalLeafCount = vis->m_dwLeafs;
        PVSState().visibleLeafPolyRefs = ctx.leafPolyRefs;
        PVSState().haveStaticPVS = !ctx.leaves.empty();
        PVSState().visibleWorldModels.swap(ctx.visibleWorldModels);
        PVSState().visibleWorldModelCount = static_cast<uint32>(PVSState().visibleWorldModels.size());
        PVSState().visibleModels.swap(ctx.visibleModels);
        PVSState().visibleDynamicLights.swap(ctx.visibleDynamicLights);
        PVSState().visibleSprites.swap(ctx.visibleSprites);
        PVSState().visibleParticleSystems.swap(ctx.visibleParticleSystems);
        PVSState().visiblePolyGrids.swap(ctx.visiblePolyGrids);
        PVSState().visibleLineSystems.swap(ctx.visibleLineSystems);
        PVSState().visibleCanvases.swap(ctx.visibleCanvases);

        std::sort(ctx.leaves.begin(), ctx.leaves.end());
        ctx.leaves.erase(std::unique(ctx.leaves.begin(), ctx.leaves.end()), ctx.leaves.end());

        static MainWorldCompat *lastWorld = nullptr;
        static uint64_t lastHash = ~0ull;
        static uint32 logBudget = 256;

        const uint64_t hash = HashVisibleLeaves(ctx.leaves);
        const bool pvsChanged = (PVSState().staticPvsWorld != world || PVSState().staticPvsHash != hash);
        if (pvsChanged)
        {
            PVSState().staticPvsWorld = world;
            PVSState().staticPvsHash = hash;
            ++PVSState().staticPvsGeneration;
            if (PVSState().staticPvsGeneration == 0)
                PVSState().staticPvsGeneration = 1;
        }

        if (!LogIsSessionEnabled())
            return true;

        if (lastWorld == world && lastHash == hash)
            return true;

        lastWorld = world;
        lastHash = hash;

        if (logBudget == 0)
            return true;
        --logBudget;

        std::ostringstream ss;
        const size_t shown = std::min<size_t>(ctx.leaves.size(), 64);
        for (size_t i = 0; i < shown; ++i)
        {
            if (i)
                ss << ',';
            ss << ctx.leaves[i];
        }
        if (ctx.leaves.size() > shown)
            ss << ",...";

        LOG_SESSION("World3D ENGINE PVS visibleLeaves=%u/%u objectCallbacks=%u worldmodels=%u models=%u sprites=%u dynLights=%u leafPolyRefs=%u uniqueStaticPolys=%u portalTests=%u portalRejected=%u nodeTests=%u nodeRejected=%u cam=(%.2f %.2f %.2f) leaves=[%s]",
                    static_cast<unsigned>(ctx.leaves.size()), vis->m_dwLeafs,
                    ctx.objectCallbacks, PVSState().visibleWorldModelCount,
                    static_cast<unsigned>(PVSState().visibleModels.size()),
                    static_cast<unsigned>(PVSState().visibleSprites.size()),
                    static_cast<unsigned>(PVSState().visibleDynamicLights.size()), ctx.leafPolyRefs,
                    static_cast<unsigned>(PVSState().visibleStaticPolys.size()),
                    ctx.portalTests, ctx.portalRejected, ctx.nodeTests, ctx.nodeRejected,
                    camera.x, camera.y, camera.z, ss.str().c_str());

        // Dump the visibility-list metadata for only the leaves Talon itself
        // reported visible. This avoids guessing which leaf contains the camera.
        const size_t detailCount = std::min<size_t>(ctx.leaves.size(), 12);
        for (size_t i = 0; i < detailCount; ++i)
        {
            const uint32 li = ctx.leaves[i];
            LeafCompat &leaf = vis->m_pLeafs[li];
            LOG_SESSION("World3D ENGINE PVS LEAF index=%u lists=%u polies=%u listPtr=%p",
                        li, leaf.m_nLists, leaf.m_dwPolies, leaf.m_pLists);

            const uint32 n = std::min<uint32>(leaf.m_nLists, 4);
            for (uint32 j = 0; j < n && leaf.m_pLists; ++j)
            {
                const LeafListCompat &list = leaf.m_pLists[j];
                LOG_SESSION("World3D ENGINE PVS LIST leaf=%u list=%u portal=%u size=%u data=%p bytes=%s",
                            li, j, list.m_wPortalID, list.m_wSize, list.m_pVisData,
                            HexVisPrefix(list.m_pVisData, list.m_wSize, 32).c_str());
            }
        }

        return true;
    }

    // -------------------------------------------------------------------------
    // Stock d3d.ren full object-manager enumeration path.
    // d3d.ren 0x10039510 selects 0x10039540(fullEnum=1) unless
    // MainWorld::m_dwFlags (+0x180) has bit 0x2 set and a renderer override is
    // clear.  fullEnum=1 calls MainWorld vfunc[1] to obtain the engine object
    // manager, then 0x10039100 walks every object bucket instead of WorldTree PVS.
    //
    // We mirror the primary object-bucket walk here and merge those objects into
    // the same visible sets.  This is particularly important for cinematic
    // objects that can leave the WorldTree visibility set while remaining active
    // in the engine object manager.
    // -------------------------------------------------------------------------
    struct ObjMgrLinkCompat
    {
        ObjMgrLinkCompat *m_pNext; // +0
        ObjMgrLinkCompat *m_pPrev; // +4
        LTObjectCompat *m_pData;   // +8
    };

    struct ObjMgrBucketCompat
    {
        uint8 m_pad0_11[12];
        ObjMgrLinkCompat m_Head; // +12
    };
    static_assert(sizeof(ObjMgrBucketCompat) == 24, "ObjMgr bucket size mismatch");

    struct ObjectMgrCompat
    {
        uint8 m_pad0_111[112];
        ObjMgrBucketCompat *m_pBuckets; // +0x70
        uint32 m_dwBucketCount;         // +0x74
        uint8 m_pad120_159[40];
        LTObjectCompat **m_ppSpecial; // +0xA0
        uint32 m_dwSpecialCount;      // +0xA4
    };

    using GetObjectMgrCompatFn = void *(__fastcall *)(MainWorldCompat *, void *);

    static bool MergeObjectManagerObjects(MainWorldCompat *world)
    {
        if (!world || !world->m_pVTable)
            return false;

        auto fn = reinterpret_cast<GetObjectMgrCompatFn>(world->m_pVTable[1]);
        if (!fn)
            return false;

        auto *mgr = reinterpret_cast<ObjectMgrCompat *>(fn(world, nullptr));
        if (!mgr)
        {
            static int nullBudget = 8;
            if (LogIsSessionEnabled() && ((nullBudget > 0 && nullBudget--)))
                LOG_SESSION("World3D FULLENUM object manager unavailable world=%p flags=%08X", world, world->m_dwFlags);
            return false;
        }

        if (!mgr->m_pBuckets || mgr->m_dwBucketCount == 0 || mgr->m_dwBucketCount > 4096)
        {
            static int badBudget = 8;
            if (LogIsSessionEnabled() && ((badBudget > 0 && badBudget--)))
                LOG_SESSION("World3D FULLENUM bad manager=%p buckets=%p count=%u worldFlags=%08X",
                            mgr, mgr->m_pBuckets, mgr->m_dwBucketCount, world->m_dwFlags);
            return false;
        }

        EnginePVSContext ctx;
        // Seed with whatever the PVS pass already found.  This preserves static
        // world visibility while adding the stock full-enumeration object source.
        ctx.visibleWorldModels = PVSState().visibleWorldModels;
        ctx.visibleModels = PVSState().visibleModels;
        ctx.visibleDynamicLights = PVSState().visibleDynamicLights;
        ctx.visibleSprites = PVSState().visibleSprites;
        ctx.visibleParticleSystems = PVSState().visibleParticleSystems;
        ctx.visiblePolyGrids = PVSState().visiblePolyGrids;
        ctx.visibleLineSystems = PVSState().visibleLineSystems;
        ctx.visibleCanvases = PVSState().visibleCanvases;
        for (auto *p : PVSState().visibleWorldModels)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleModels)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleDynamicLights)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleSprites)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleParticleSystems)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visiblePolyGrids)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleLineSystems)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);
        for (auto *p : PVSState().visibleCanvases)
            if (p)
                ctx.seenObjects.insert(&p->m_Base);

        uint32 roots = 0, added = 0, attachments = 0;
        for (uint32 bi = 0; bi < mgr->m_dwBucketCount; ++bi)
        {
            ObjMgrLinkCompat *head = &mgr->m_pBuckets[bi].m_Head;
            ObjMgrLinkCompat *cur = head->m_pNext;
            uint32 guard = 0;
            while (cur && cur != head && guard++ < 65536)
            {
                LTObjectCompat *obj = cur->m_pData;
                ++roots;
                if (obj && obj->m_pSrvObjData == nullptr)
                {
                    const bool wasSeen = ctx.seenObjects.find(obj) != ctx.seenObjects.end();
                    const bool accepted = EnginePVS_AddResolvedObject(&ctx, obj, true);
                    if (accepted && !wasSeen)
                        ++added;

                    // 0x100391CB onward: full-enum also resolves attachments for
                    // each accepted root through the renderer attachment callback.
                    RenderStruct *rs = WorldRenderer::Instance().GetRenderStruct();
                    if (accepted && obj->m_pAttachments && rs && rs->ProcessAttachment)
                    {
                        uint32 ag = 0;
                        for (Attachment *a = obj->m_pAttachments; a && ag++ < 4096; a = a->m_pNext)
                        {
                            auto *child = reinterpret_cast<LTObjectCompat *>(
                                rs->ProcessAttachment(reinterpret_cast<LTObject *>(obj), a));
                            if (!child)
                                continue;
                            const bool childSeen = ctx.seenObjects.find(child) != ctx.seenObjects.end();
                            if (EnginePVS_AddResolvedObject(&ctx, child, false) && !childSeen)
                            {
                                ++attachments;
                                static int childBudget = 64;
                                if (LogIsSessionEnabled() && ((childBudget > 0 && childBudget--)))
                                    LOG_SESSION("World3D FULLENUM-ATTACH parent=%p child=%p type=%u flags=%08X internal=%08X pos=(%.2f %.2f %.2f)",
                                                obj, child, unsigned(child->m_nObjectType), child->m_dwFlags, child->m_dwInternalFlags,
                                                child->m_vPos.x, child->m_vPos.y, child->m_vPos.z);
                            }
                        }
                    }
                }
                cur = cur->m_pNext;
            }
        }

        PVSState().visibleWorldModels.swap(ctx.visibleWorldModels);
        PVSState().visibleWorldModelCount = static_cast<uint32>(PVSState().visibleWorldModels.size());
        PVSState().visibleModels.swap(ctx.visibleModels);
        PVSState().visibleDynamicLights.swap(ctx.visibleDynamicLights);
        PVSState().visibleSprites.swap(ctx.visibleSprites);
        PVSState().visibleParticleSystems.swap(ctx.visibleParticleSystems);
        PVSState().visiblePolyGrids.swap(ctx.visiblePolyGrids);
        PVSState().visibleLineSystems.swap(ctx.visibleLineSystems);
        PVSState().visibleCanvases.swap(ctx.visibleCanvases);

        static uint32 lastAdded = 0xFFFFFFFFu, lastRoots = 0xFFFFFFFFu, lastAtt = 0xFFFFFFFFu;
        if (LogIsSessionEnabled() && (lastAdded != added || lastRoots != roots || lastAtt != attachments))
        {
            lastAdded = added;
            lastRoots = roots;
            lastAtt = attachments;
            LOG_SESSION("World3D FULLENUM worldFlags=%08X mgr=%p buckets=%u roots=%u added=%u attachments=%u totals wm=%u models=%u sprites=%u particles=%u polygrids=%u lines=%u canvases=%u",
                        world->m_dwFlags, mgr, mgr->m_dwBucketCount, roots, added, attachments,
                        unsigned(PVSState().visibleWorldModels.size()), unsigned(PVSState().visibleModels.size()), unsigned(PVSState().visibleSprites.size()),
                        unsigned(PVSState().visibleParticleSystems.size()), unsigned(PVSState().visiblePolyGrids.size()),
                        unsigned(PVSState().visibleLineSystems.size()), unsigned(PVSState().visibleCanvases.size()));
        }
        return true;
    }

    static void AuditObjectManagerDropships(MainWorldCompat *world, const LTVector &camera)
    {
        if (!LogIsSessionEnabled())
            return;
        if (!world || !world->m_pVTable)
            return;
        auto fn = reinterpret_cast<GetObjectMgrCompatFn>(world->m_pVTable[1]);
        if (!fn)
            return;
        auto *mgr = reinterpret_cast<ObjectMgrCompat *>(fn(world, nullptr));
        if (!mgr || !mgr->m_pBuckets || mgr->m_dwBucketCount == 0 || mgr->m_dwBucketCount > 4096)
            return;

        static uint32 lastFrame = 0;
        static uint32 frameCounter = 0;
        ++frameCounter;
        if (frameCounter - lastFrame < 30)
            return;
        lastFrame = frameCounter;

        uint32 models = 0, dropships = 0;
        for (uint32 bi = 0; bi < mgr->m_dwBucketCount; ++bi)
        {
            ObjMgrLinkCompat *head = &mgr->m_pBuckets[bi].m_Head;
            ObjMgrLinkCompat *cur = head->m_pNext;
            uint32 guard = 0;
            while (cur && cur != head && guard++ < 65536)
            {
                LTObjectCompat *obj = cur->m_pData;
                if (obj && obj->m_nObjectType == OT_MODEL)
                {
                    ++models;
                    auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
                    Model *model = GetModelFromInstance(inst);
                    const char *name = (model && model->m_szFilename) ? model->m_szFilename : "";
                    if (strstr(name, "dropship") || strstr(name, "Dropship") || strstr(name, "DROPSHIP"))
                    {
                        ++dropships;
                        const float dx = obj->m_vPos.x - camera.x;
                        const float dy = obj->m_vPos.y - camera.y;
                        const float dz = obj->m_vPos.z - camera.z;
                        const float d2 = dx * dx + dy * dy + dz * dz;
                        LOG_SESSION("World3D OBJMGR-AUDIT DROPSHIP obj=%p model='%s' bucket=%u pos=(%.2f %.2f %.2f) dist=%.2f flags=%08X flags2=%08X internal=%08X srv=%p attach=%p wtFrame=%08X",
                                    obj, name, bi, obj->m_vPos.x, obj->m_vPos.y, obj->m_vPos.z, std::sqrt(d2),
                                    obj->m_dwFlags, obj->m_dwFlags2, obj->m_dwInternalFlags, obj->m_pSrvObjData, obj->m_pAttachments, obj->m_dwWTFrameCode);
                    }
                }
                cur = cur->m_pNext;
            }
        }
        static uint32 lastDrops = 0xFFFFFFFFu, lastModels = 0xFFFFFFFFu;
        if (lastDrops != dropships || lastModels != models)
        {
            lastDrops = dropships;
            lastModels = models;
            LOG_SESSION("World3D OBJMGR-AUDIT SUMMARY mgr=%p buckets=%u models=%u dropships=%u cam=(%.2f %.2f %.2f)",
                        mgr, mgr->m_dwBucketCount, models, dropships, camera.x, camera.y, camera.z);
        }
    }

} // namespace

bool WorldPVS::Query(MainWorldCompat *world, WorldBspCompat *vis, SceneDesc *scene)
{
    return QueryEnginePVS(world, vis, scene);
}

bool WorldPVS::MergeObjectManager(MainWorldCompat *world)
{
    return MergeObjectManagerObjects(world);
}

void WorldPVS::AuditObjectManager(MainWorldCompat *world, const LTVector &camera)
{
    AuditObjectManagerDropships(world, camera);
}

WorldPVS &WorldPVS::Instance()
{
    static WorldPVS instance;
    return instance;
}

void WorldPVS::Reset()
{
    m_state.visibleStaticPolys.clear();
    m_state.visibleStaticMaskBsp = nullptr;
    m_state.visibleStaticMask.clear();
    m_state.haveStaticPVS = false;
    m_state.visibleLeafCount = 0;
    m_state.visibleLeafPolyRefs = 0;
    m_state.totalLeafCount = 0;
    m_state.visibleWorldModels.clear();
    m_state.visibleModels.clear();
    m_state.visibleDynamicLights.clear();
    m_state.visibleSprites.clear();
    m_state.visibleParticleSystems.clear();
    m_state.visiblePolyGrids.clear();
    m_state.visibleLineSystems.clear();
    m_state.visibleCanvases.clear();
    m_state.visibleWorldModelCount = 0;
    m_state.staticPvsWorld = nullptr;
    m_state.staticPvsHash = ~uint64_t(0);
    m_state.staticPvsGeneration = 1;
    m_state.perfStats = {};
}

uint32 WorldPVS::GetModelCount() const { return static_cast<uint32>(m_state.visibleModels.size()); }
ModelInstanceCompat *WorldPVS::GetModel(uint32 i) const { return i < m_state.visibleModels.size() ? m_state.visibleModels[i] : nullptr; }
uint32 WorldPVS::GetSpriteCount() const { return static_cast<uint32>(m_state.visibleSprites.size()); }
SpriteInstanceCompat *WorldPVS::GetSprite(uint32 i) const { return i < m_state.visibleSprites.size() ? m_state.visibleSprites[i] : nullptr; }
uint32 WorldPVS::GetParticleSystemCount() const { return static_cast<uint32>(m_state.visibleParticleSystems.size()); }
ParticleSystemCompat *WorldPVS::GetParticleSystem(uint32 i) const { return i < m_state.visibleParticleSystems.size() ? m_state.visibleParticleSystems[i] : nullptr; }
uint32 WorldPVS::GetPolyGridCount() const { return static_cast<uint32>(m_state.visiblePolyGrids.size()); }
PolyGridCompat *WorldPVS::GetPolyGrid(uint32 i) const { return i < m_state.visiblePolyGrids.size() ? m_state.visiblePolyGrids[i] : nullptr; }
uint32 WorldPVS::GetLineSystemCount() const { return static_cast<uint32>(m_state.visibleLineSystems.size()); }
LineSystemCompat *WorldPVS::GetLineSystem(uint32 i) const { return i < m_state.visibleLineSystems.size() ? m_state.visibleLineSystems[i] : nullptr; }
uint32 WorldPVS::GetCanvasCount() const { return static_cast<uint32>(m_state.visibleCanvases.size()); }
CanvasCompat *WorldPVS::GetCanvas(uint32 i) const { return i < m_state.visibleCanvases.size() ? m_state.visibleCanvases[i] : nullptr; }
uint32 WorldPVS::GetDynamicLightCount() const { return static_cast<uint32>(m_state.visibleDynamicLights.size()); }
DynamicLightCompat *WorldPVS::GetDynamicLight(uint32 i) const { return i < m_state.visibleDynamicLights.size() ? m_state.visibleDynamicLights[i] : nullptr; }
