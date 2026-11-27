#include "scene_renderer.h"
#include "../models/abc_model_renderer.h"
#include "../renderer/frame_constants.h"
#include "../renderer/renderer_core.h"
#include "../renderer/renderer_2d.h"
#include "../renderer/gui_quality.h"
#include "../sprites/sprite_renderer.h"
#include "../fx/fx_renderer.h"
#include "../world/world_renderer.h"
#include "gl_loader.h"
#include "gl_renderer.h"
#include "utils/log.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <unordered_set>

namespace
{
    uint64_t g_sceneCount = 0;
    uint64_t g_lastFrameModelTris = 0;
    uint32 g_lastFrameModelsDrawn = 0;
    ULONGLONG g_lastStats = 0;
    bool g_loadingObjectList = false;

    bool RenderModel(SceneDesc *scene, ModelInstanceCompat *model, bool translucent = false)
    {
        return ABCModelRenderer::Instance().Render(scene, model, translucent, g_loadingObjectList);
    }
    static void LogSceneTypes(SceneDesc *scene)
    {
        if (!LogIsSessionEnabled())
            return;
        if (!scene)
            return;

        uint32 counts[11] = {};
        uint64_t sig = 1469598103934665603ull;
        for (int i = 0; i < scene->m_nObjectListSize; ++i)
        {
            auto *o = (scene->m_pObjectList) ? reinterpret_cast<LTObjectCompat *>(scene->m_pObjectList[i]) : nullptr;
            if (o && o->m_nObjectType < 11)
                counts[o->m_nObjectType]++;
            const uintptr_t v = reinterpret_cast<uintptr_t>(o);
            sig ^= static_cast<uint64_t>(v);
            sig *= 1099511628211ull;
            if (o)
            {
                sig ^= static_cast<uint64_t>(o->m_nObjectType);
                sig *= 1099511628211ull;
            }
        }

        // d3d.ren 0x10014AE9 takes a completely separate path when drawMode==2:
        // it walks SceneDesc::m_pObjectList directly instead of calling the
        // WorldTree population routine at 0x10039510.  Log every distinct object
        // list so cinematic scene transitions are visible without flooding every
        // frame with identical data.
        static uint64_t lastSig = ~0ull;
        static int lastMode = -999;
        static int lastCount = -1;
        const bool changed = (sig != lastSig) || (scene->m_nDrawMode != lastMode) ||
                             (scene->m_nObjectListSize != lastCount);
        if (!changed)
            return;

        lastSig = sig;
        lastMode = scene->m_nDrawMode;
        lastCount = scene->m_nObjectListSize;

        LOG_SESSION("D3D-SCENE-PATH mode=%d path=%s objects=%d list=%p viewport=(%d,%d)-(%d,%d) fov=(%.4f,%.4f) far=%.2f types model=%u wm=%u sprite=%u light=%u particle=%u polygrid=%u lines=%u canvases=%u",
                    scene->m_nDrawMode,
                    scene->m_nDrawMode == DRAWMODE_OBJECTLIST ? "OBJECTLIST-DIRECT" : "NORMAL-WORLD",
                    scene->m_nObjectListSize, scene->m_pObjectList,
                    scene->m_rcViewport.m_nLeft, scene->m_rcViewport.m_nTop,
                    scene->m_rcViewport.m_nRight, scene->m_rcViewport.m_nBottom,
                    scene->m_fFovX, scene->m_fFovY, scene->m_fFarZ,
                    counts[OT_MODEL], counts[OT_WORLDMODEL], counts[OT_SPRITE],
                    counts[OT_LIGHT], counts[OT_PARTICLESYSTEM], counts[OT_POLYGRID],
                    counts[OT_LINESYSTEM], counts[OT_CANVAS]);

        if (scene->m_pObjectList)
        {
            for (int i = 0; i < scene->m_nObjectListSize; ++i)
            {
                auto *o = reinterpret_cast<LTObjectCompat *>(scene->m_pObjectList[i]);
                if (!o)
                    continue;
                // Models are the important part for the m_open cinematic, but
                // include attachment-bearing roots of any type as well.
                if (o->m_nObjectType == OT_MODEL || o->m_pAttachments)
                {
                    LOG_SESSION("D3D-SCENE-OBJ src=%d obj=%p type=%u flags=%08X flags2=%08X internal=%08X attach=%p pos=(%.2f %.2f %.2f)",
                                i, o, static_cast<unsigned>(o->m_nObjectType), o->m_dwFlags, o->m_dwFlags2,
                                o->m_dwInternalFlags, o->m_pAttachments,
                                o->m_vPos.x, o->m_vPos.y, o->m_vPos.z);
                }
            }
        }
    }
}

struct QueuedSprite
{
    SpriteInstanceCompat *sprite = nullptr;
    float distanceSq = 0.0f;
    float radius = 0.0f;
    uint32 specialBlendBits = 0;
    bool reallyClose = false;
    int sourceIndex = 0;
};

static float SpriteDistanceSq(const SceneDesc *scene, const LTObjectCompat &o)
{
    if (o.m_dwFlags & FLAG_REALLYCLOSE)
    {
        return o.m_vPos.x * o.m_vPos.x +
               o.m_vPos.y * o.m_vPos.y +
               o.m_vPos.z * o.m_vPos.z;
    }

    const float x = o.m_vPos.x - scene->m_vPos.x;
    const float y = o.m_vPos.y - scene->m_vPos.y;
    const float z = o.m_vPos.z - scene->m_vPos.z;
    return x * x + y * y + z * z;
}

static bool SpriteQueueBefore(const QueuedSprite &a, const QueuedSprite &b)
{
    // Mirrors ObjectDrawer::operator< + std::priority_queue behavior from
    // the D3D11 reference renderer, expressed directly as draw order.

    // Normal-space translucent objects are flushed before ReallyClose ones.
    if (a.reallyClose != b.reallyClose)
        return !a.reallyClose && b.reallyClose;

    const float distA = std::sqrt(std::max(0.0f, a.distanceSq));
    const float distB = std::sqrt(std::max(0.0f, b.distanceSq));

    // Large menu sprites (planet, beam, glows) can overlap heavily in depth.
    // When their approximate sphere depth ranges overlap, preserve source
    // order rather than forcing a center-point sort that can invert intended
    // layering.
    const float nearA = distA - a.radius;
    const float farA = distA + a.radius;
    const float nearB = distB - b.radius;
    const float farB = distB + b.radius;
    const bool depthOverlap = (nearA <= farB) && (nearB <= farA);
    if (depthOverlap)
        return a.sourceIndex < b.sourceIndex;

    // Otherwise translucent draw is back-to-front.
    if (a.distanceSq != b.distanceSq)
        return a.distanceSq > b.distanceSq;

    // Reference tie-break: smaller radius wins priority_queue top.
    if (a.radius != b.radius)
        return a.radius < b.radius;

    // Default blend comes before ADDITIVE/MULTIPLY when all else ties.
    if (a.specialBlendBits != b.specialBlendBits)
        return a.specialBlendBits < b.specialBlendBits;

    // Keep ordering deterministic when the reference comparator considers
    // objects equivalent.
    return a.sourceIndex < b.sourceIndex;
}

static void SetupScenePipeline(SceneDesc *scene)
{
    const int vx = scene->m_rcViewport.m_nLeft;
    const int vyTop = scene->m_rcViewport.m_nTop;
    const int vw = std::max(1, scene->m_rcViewport.m_nRight - scene->m_rcViewport.m_nLeft);
    const int vh = std::max(1, scene->m_rcViewport.m_nBottom - scene->m_rcViewport.m_nTop);
    const int vy = RendererCore::Instance().Height() - (vyTop + vh);

    glViewport(vx, vy, vw, vh);

    // Talon's menu/object-list scenes render into the centered 640x480 menu
    // frame even when the scene viewport covers the whole backbuffer.
    // RenderDoc/screenshot evidence shows the 3D model layer must be clipped
    // to that frame so the surrounding fade-out border remains in front.
    int sx = vx, sy = vy, sw = vw, sh = vh;
    if (scene->m_nDrawMode == DRAWMODE_OBJECTLIST)
    {
        const int menuW = std::min(640, vw);
        const int menuH = std::min(480, vh);
        const int menuLeft = vx + (vw - menuW) / 2;
        const int menuTop = vyTop + (vh - menuH) / 2;
        sx = menuLeft;
        sy = RendererCore::Instance().Height() - (menuTop + menuH);
        sw = menuW;
        sh = menuH;
    }

    GLStateEnable(GL_SCISSOR_TEST);
    glScissor(sx, sy, sw, sh);
    GLStateEnable(GL_DEPTH_TEST);
    GLStateDepthFunc(GL_LEQUAL);
    GLStateDepthMask(GL_TRUE);
    GLStateDisable(GL_CULL_FACE);

    ABCModelRenderer::Instance().BindPipeline();

    const float tanHalfX = std::tan(std::max(0.01f, scene->m_fFovX * 0.5f));
    const float tanHalfY = std::tan(std::max(0.01f, scene->m_fFovY * 0.5f));
    const float nearZ = 1.0f;
    const float farZ = std::max(nearZ + 1.0f, scene->m_fFarZ);

    FrameConstants::Instance().Apply(scene, tanHalfX, tanHalfY, nearZ, farZ);
}

static void CollectProcessedAttachments(LTObjectCompat *parent,
                                        std::vector<ModelInstanceCompat *> &out,
                                        std::unordered_set<LTObjectCompat *> &visited,
                                        uint32 depth = 0)
{
    if (!parent || depth > 16 || !SceneRenderer::Instance().GetRenderStruct() || !SceneRenderer::Instance().GetRenderStruct()->ProcessAttachment)
        return;

    for (Attachment *a = parent->m_pAttachments; a; a = a->m_pNext)
    {
        LTObject *childRaw = SceneRenderer::Instance().GetRenderStruct()->ProcessAttachment(
            reinterpret_cast<LTObject *>(parent), a);
        auto *child = reinterpret_cast<LTObjectCompat *>(childRaw);
        if (!child || !visited.insert(child).second)
            continue;

        static int attachLogBudget = 48;
        if (LogIsSessionEnabled() && ((attachLogBudget > 0 && attachLogBudget--)))
        {
            LOG_SESSION("Model3D ATTACH parent=%p child=%p type=%u socket=%u pos=(%.2f %.2f %.2f)",
                        parent, child, static_cast<unsigned>(child->m_nObjectType),
                        static_cast<unsigned>(a->m_iSocket),
                        child->m_vPos.x, child->m_vPos.y, child->m_vPos.z);
        }

        if (child->m_nObjectType == OT_MODEL && (child->m_dwFlags & FLAG_VISIBLE))
            out.push_back(reinterpret_cast<ModelInstanceCompat *>(child));

        CollectProcessedAttachments(child, out, visited, depth + 1);
    }
}

static bool IsLocalThirdPersonParent(SceneDesc *, ModelInstanceCompat *)
{
    // M3.14.4: no renderer-side camera-position heuristic.
    // Stock d3d.ren relies on WorldTree/DoVisQuery object submission.
    return false;
}

static void RenderVisibleEffectsFromPVS(SceneDesc *scene, bool reallyClosePass);

struct StockTranslucentItem
{
    LTObjectCompat *obj = nullptr;
    float dist2 = 0.0f;
    uint32 sourceOrder = 0;
};

static float StockObjectDistanceSq(const SceneDesc *scene, const LTObjectCompat *o)
{
    if (!scene || !o)
        return 0.0f;
    if (o->m_dwFlags & FLAG_REALLYCLOSE)
        return o->m_vPos.x * o->m_vPos.x + o->m_vPos.y * o->m_vPos.y + o->m_vPos.z * o->m_vPos.z;
    const float x = o->m_vPos.x - scene->m_vPos.x;
    const float y = o->m_vPos.y - scene->m_vPos.y;
    const float z = o->m_vPos.z - scene->m_vPos.z;
    return x * x + y * y + z * z;
}

static bool IsStockSolidCanvas(const CanvasCompat *canvas)
{
    // d3d.ren 0x10022B99..0x10022BB8: client-flags byte +0x188 bit 0x10
    // is drawn immediately in the solid-canvas pass; otherwise the Canvas is
    // copied to the sorted translucent-canvas set.
    return canvas && ((canvas->m_Base.m_dwClientFlags & 0x10u) != 0);
}

static bool IsStockTranslucentPolyGrid(const PolyGridCompat *grid)
{
    if (!grid)
        return false;
    const LTObjectCompat &o = grid->m_Base;
    // Retail keeps separate VS_POLYGRIDS and VS_POLYGRIDS_TRANSLUCENT buckets.
    // Object alpha and explicit additive/multiply material flags are the
    // renderer-visible conditions that require compositing.  Alpha-255 normal
    // PolyGrids belong to the solid bucket and must write depth before the
    // common translucent list is flushed.
    return o.m_nColorA < 255 || (o.m_dwFlags2 & (FLAG2_ADDITIVE | FLAG2_MULTIPLY)) != 0;
}

static void RenderSolidPolyGridsFromPVS(SceneDesc *scene)
{
    uint32 drawn = 0;
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetPolyGridCount(); ++i)
    {
        PolyGridCompat *grid = WorldRenderer::Instance().PVS().GetPolyGrid(i);
        if (!grid || !(grid->m_Base.m_dwFlags & FLAG_VISIBLE) ||
            (grid->m_Base.m_dwFlags & FLAG_REALLYCLOSE) || IsStockTranslucentPolyGrid(grid))
            continue;
        if (FXRenderer::Instance().RenderPolyGrid(scene, grid))
            ++drawn;
    }
    static int budget = 32;
    if (LogIsSessionEnabled() && (drawn && (budget > 0 && budget--)))
        LOG_SESSION("FX3D POLYGRID SOLID count=%u split=VS_POLYGRIDS", drawn);
}

static void RenderSolidCanvasesFromPVS(SceneDesc *scene)
{
    uint32 drawn = 0;
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetCanvasCount(); ++i)
    {
        CanvasCompat *canvas = WorldRenderer::Instance().PVS().GetCanvas(i);
        if (!canvas || !(canvas->m_Base.m_dwFlags & FLAG_VISIBLE) || !IsStockSolidCanvas(canvas))
            continue;
        if (FXRenderer::Instance().RenderCanvas(scene, canvas))
            ++drawn;
    }
    static int budget = 32;
    if (LogIsSessionEnabled() && (drawn && (budget > 0 && budget--)))
        LOG_SESSION("FX3D CANVAS SOLID count=%u split=D3D-0x10022B50-clientFlag10", drawn);
}

static bool IsAttachedWorldDecalSprite(const SpriteInstanceCompat *sprite)
{
    if (!sprite)
        return false;
    const LTObjectCompat &o = sprite->m_Base;
    return (o.m_dwFlags & FLAG_VISIBLE) &&
           !(o.m_dwFlags & FLAG_REALLYCLOSE) &&
           !(o.m_dwFlags & FLAG_SPRITE_NOZ) &&
           (o.m_dwFlags & FLAG_ROTATEABLESPRITE) &&
           sprite->m_hClipperPoly != 0xFFFFFFFFu;
}

static void RenderStockTranslucentStage(SceneDesc *scene,
                                        const std::vector<ModelInstanceCompat *> &models)
{
    std::vector<StockTranslucentItem> items;
    std::vector<SpriteInstanceCompat *> attachedDecals;
    const uint32 twmCount = WorldRenderer::Instance().Visibility().GetTranslucentWorldModelCount();
    items.reserve(twmCount + models.size() + WorldRenderer::Instance().PVS().GetSpriteCount() +
                  WorldRenderer::Instance().PVS().GetParticleSystemCount() + WorldRenderer::Instance().PVS().GetPolyGridCount() +
                  WorldRenderer::Instance().PVS().GetLineSystemCount() + WorldRenderer::Instance().PVS().GetCanvasCount());
    uint32 order = 0;

    // d3d.ren 0x10028882 queues translucent WorldModels into this SAME
    // distance-sorted list before translucent models.
    for (uint32 i = 0; i < twmCount; ++i)
    {
        WorldModelInstanceCompat *wm = WorldRenderer::Instance().Visibility().GetTranslucentWorldModel(i);
        LTObjectCompat *o = wm ? &wm->m_Base : nullptr;
        if (!o || !(o->m_dwFlags & FLAG_VISIBLE) || (o->m_dwFlags & FLAG_REALLYCLOSE))
            continue;
        items.push_back({o, StockObjectDistanceSq(scene, o), order++});
    }

    for (ModelInstanceCompat *m : models)
    {
        auto *o = m ? &m->m_Base : nullptr;
        if (!o || !(o->m_dwFlags & FLAG_VISIBLE) || (o->m_dwFlags & FLAG_REALLYCLOSE))
            continue;
        items.push_back({o, StockObjectDistanceSq(scene, o), order++});
    }

    auto addEffect = [&](LTObjectCompat *o)
    {
        if (!o || !(o->m_dwFlags & FLAG_VISIBLE) || (o->m_dwFlags & FLAG_REALLYCLOSE))
            return;
        if (o->m_nObjectType == OT_SPRITE && (o->m_dwFlags & FLAG_SPRITE_NOZ))
            return;
        items.push_back({o, StockObjectDistanceSq(scene, o), order++});
    };
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetParticleSystemCount(); ++i)
        addEffect(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetParticleSystem(i)));
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetPolyGridCount(); ++i)
    {
        PolyGridCompat *grid = WorldRenderer::Instance().PVS().GetPolyGrid(i);
        if (IsStockTranslucentPolyGrid(grid))
            addEffect(reinterpret_cast<LTObjectCompat *>(grid));
    }
    // d3d.ren 0x10028874 queues OT_LINESYSTEM into this same translucent
    // distance-sorted object list.
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetLineSystemCount(); ++i)
        addEffect(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetLineSystem(i)));
    // d3d.ren 0x1002889D queues only the non-solid Canvas subset into the
    // common distance-sorted translucent object list.
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetCanvasCount(); ++i)
    {
        CanvasCompat *c = WorldRenderer::Instance().PVS().GetCanvas(i);
        if (c && !IsStockSolidCanvas(c))
            addEffect(&c->m_Base);
    }
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetSpriteCount(); ++i)
    {
        SpriteInstanceCompat *sprite = WorldRenderer::Instance().PVS().GetSprite(i);
        if (IsAttachedWorldDecalSprite(sprite))
            attachedDecals.push_back(sprite);
        else
            addEffect(reinterpret_cast<LTObjectCompat *>(sprite));
    }

    std::stable_sort(items.begin(), items.end(), [](const StockTranslucentItem &a, const StockTranslucentItem &b)
                     {
        if(a.dist2!=b.dist2) return a.dist2>b.dist2;
        // Retail's sorted-list insertion is stable for equal sort keys.  Keep
        // the bucket insertion order instead of inventing a per-type priority.
        return a.sourceOrder<b.sourceOrder; });

    static int orderBudget = 24;
    if (LogIsSessionEnabled() && ((orderBudget > 0 && orderBudget--) && !items.empty()))
    {
        const uint32 n = static_cast<uint32>(std::min<size_t>(items.size(), 12));
        LOG_SESSION("Model3D STOCK-TRANS-ORDER total=%u showing=%u", unsigned(items.size()), n);
        for (uint32 i = 0; i < n; ++i)
            LOG_SESSION("  TRANSQ[%u] type=%u dist2=%.2f src=%u obj=%p flags=%08X flags2=%08X alpha=%u",
                        i, unsigned(items[i].obj->m_nObjectType), items[i].dist2, items[i].sourceOrder, items[i].obj,
                        items[i].obj->m_dwFlags, items[i].obj->m_dwFlags2, unsigned(items[i].obj->m_nColorA));
    }

    uint32 wmDrawn = 0, md = 0, sp = 0, ps = 0, pg = 0, ls = 0, cv = 0;
    GLStateEnable(GL_DEPTH_TEST);
    GLStateDepthFunc(GL_LEQUAL);
    GLStateDepthRange(0.0, 1.0);
    GLStateDepthMask(GL_FALSE);
    static int depthContractBudget = 32;
    if (LogIsSessionEnabled() && ((depthContractBudget > 0 && depthContractBudget--)))
        LOG_SESSION("Model3D TRANS-DEPTH-CONTRACT test=1 func=LEQUAL range=0..1 zwrite=0 items=%u",
                    static_cast<unsigned>(items.size()));

    // The shared translucent list is normal world-space rendering.
    // Keep its depth range pinned to the world range so a callback using a
    // special/ReallyClose depth range cannot make the next translucent ABC
    // appear in front of opaque BSP or WorldModels.

    // World-attached marks belong on the opaque surface, not at an
    // arbitrary position inside the transparent object sort.  Draw them
    // first with Z testing and no Z writes.  Every normal translucent effect
    // (explosions, smoke, particles, translucent models/worldmodels) is then
    // composited after them and can correctly cover a mark in the background.
    uint32 decalDrawn = 0;
    for (SpriteInstanceCompat *decal : attachedDecals)
    {
        if (SpriteRenderer::Instance().Render(scene, decal))
            ++decalDrawn;
        GLStateDepthMask(GL_FALSE);
        ABCModelRenderer::Instance().BindPipeline();
    }

    for (const StockTranslucentItem &it : items)
    {
        switch (it.obj->m_nObjectType)
        {
        case OT_WORLDMODEL:
        case OT_CONTAINER:
            WorldRenderer::Instance().WorldModels().RenderTranslucent(scene, reinterpret_cast<WorldModelInstanceCompat *>(it.obj));
            ++wmDrawn;
            break;
        case OT_MODEL:
            if (RenderModel(scene, reinterpret_cast<ModelInstanceCompat *>(it.obj), true))
                ++md;
            break;
        case OT_SPRITE:
            SpriteRenderer::Instance().Render(scene, reinterpret_cast<SpriteInstanceCompat *>(it.obj));
            ++sp;
            break;
        case OT_PARTICLESYSTEM:
            FXRenderer::Instance().RenderParticleSystem(scene, reinterpret_cast<ParticleSystemCompat *>(it.obj));
            ++ps;
            break;
        case OT_POLYGRID:
            FXRenderer::Instance().RenderPolyGrid(scene, reinterpret_cast<PolyGridCompat *>(it.obj));
            ++pg;
            break;
        case OT_LINESYSTEM:
            FXRenderer::Instance().RenderLineSystem(scene, reinterpret_cast<LineSystemCompat *>(it.obj));
            ++ls;
            break;
        case OT_CANVAS:
            FXRenderer::Instance().RenderCanvas(scene, reinterpret_cast<CanvasCompat *>(it.obj));
            ++cv;
            break;
        default:
            break;
        }
        // Preserve d3d.ren's outer translucent-object contract between
        // callbacks even when an individual renderer resets its own state.
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        GLStateDepthRange(0.0, 1.0);
        GLStateDepthMask(GL_FALSE);
        ABCModelRenderer::Instance().BindPipeline();
    }

    static int budget = 64;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--)))
        LOG_SESSION("Model3D STOCK-TRANS sorted=%u decalsFirst=%u worldmodels=%u models=%u sprites=%u particles=%u polygrids=%u lines=%u canvases=%u zwrite=0",
                    unsigned(items.size()), decalDrawn, wmDrawn, md, sp, ps, pg, ls, cv);
}

static void RenderNoZSpritesFromPVS(SceneDesc *scene)
{
    uint32 count = 0;
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetSpriteCount(); ++i)
    {
        auto *s = WorldRenderer::Instance().PVS().GetSprite(i);
        if (!s)
            continue;
        LTObjectCompat &o = s->m_Base;
        if (!(o.m_dwFlags & FLAG_VISIBLE) || (o.m_dwFlags & FLAG_REALLYCLOSE) ||
            !(o.m_dwFlags & FLAG_SPRITE_NOZ))
            continue;
        SpriteRenderer::Instance().Render(scene, s);
        ABCModelRenderer::Instance().BindPipeline();
        ++count;
    }
    static int budget = 16;
    if (LogIsSessionEnabled() && ((budget > 0 && budget--) && count))
        LOG_SESSION("Sprite3D STOCK-NOZ count=%u", count);
}

static void RenderVisibleSceneObjects(SceneDesc *scene)
{
    const int64_t prepStart = RendererCore::Instance().PerfTimingBegin();
    const uint32 count = WorldRenderer::Instance().PVS().GetModelCount();

    // Stock d3d.ren 0x10028660 always executes the global render phases.
    // In particular 0x10028882 -> 0x1002FF00 contributes translucent
    // WorldModels to the shared sorted translucent queue independently of
    // whether VS_MODELS contains any model objects.  Returning here when
    // count==0 drops valid translucent WorldModels such as m_open's
    // TranslucentWorldModel8/nebula3.dtx after they have already been
    // discovered and classified.
    const uint32 translucentWorldModels = WorldRenderer::Instance().Visibility().GetTranslucentWorldModelCount();
    static int noModelWorldModelBudget = 32;
    if (LogIsSessionEnabled() && (!count && translucentWorldModels && (noModelWorldModelBudget > 0 && noModelWorldModelBudget--)))
        LOG_SESSION("Model3D STOCK-FLUSH noModels=1 translucentWorldModels=%u path=D3D-0x1002FF00",
                    translucentWorldModels);

    SetupScenePipeline(scene);

    std::vector<ModelInstanceCompat *> normalModels;
    std::vector<ModelInstanceCompat *> reallyCloseModels;
    std::vector<ModelInstanceCompat *> attachmentModels;
    std::vector<ModelInstanceCompat *> pvsModels;
    std::unordered_set<ModelInstanceCompat *> collected;
    std::unordered_set<LTObjectCompat *> attachmentVisited;

    // Stock Talon does not collapse distinct model instances by proximity.
    // M3.14.2's same-ABC/2-unit heuristic could delete legitimate character
    // state. Keep only exact pointer duplicates here; WorldTree frame-code
    // handling remains responsible for traversal duplicates.
    std::unordered_set<ModelInstanceCompat *> rawSeen;
    for (uint32 i = 0; i < count; ++i)
    {
        ModelInstanceCompat *inst = WorldRenderer::Instance().PVS().GetModel(i);
        if (!inst || !(inst->m_Base.m_dwFlags & FLAG_VISIBLE))
            continue;
        if (!rawSeen.insert(inst).second)
            continue;

        // Reject the local third-person parent BEFORE attachments are walked.
        if (IsLocalThirdPersonParent(scene, inst))
            continue;

        pvsModels.push_back(inst);
    }

    // Process parent->socket attachments before any model is rendered.
    // RenderStruct::ProcessAttachment is Talon's own transform calculation,
    // so attached guns/headsets/etc inherit the current animated node/socket
    // transform rather than their stale spawn transform.
    for (ModelInstanceCompat *parent : pvsModels)
    {
        if (!parent)
            continue;
        attachmentVisited.insert(reinterpret_cast<LTObjectCompat *>(parent));
        CollectProcessedAttachments(reinterpret_cast<LTObjectCompat *>(parent),
                                    attachmentModels, attachmentVisited);
    }
    std::unordered_set<ModelInstanceCompat *> attachmentSet(attachmentModels.begin(), attachmentModels.end());

    auto collect = [&](ModelInstanceCompat *inst)
    {
        if (!inst || !(inst->m_Base.m_dwFlags & FLAG_VISIBLE))
            return;
        if (!collected.insert(inst).second)
            return;

        const uint32 effectiveFlags = ABCModelRenderer::Instance().EffectiveFlags(scene, inst);
        if (!(effectiveFlags & FLAG_VISIBLE))
            return;

        if (effectiveFlags & FLAG_REALLYCLOSE)
            reallyCloseModels.push_back(inst);
        else
            normalModels.push_back(inst);
    };

    for (ModelInstanceCompat *inst : pvsModels)
        collect(inst);

    for (ModelInstanceCompat *child : attachmentModels)
        collect(child);

    // Explicit client-side ReallyClose models may not live in a visible leaf.
    uint32 sceneRCCount = 0;
    if (scene->m_pObjectList && scene->m_nObjectListSize > 0)
    {
        for (int i = 0; i < scene->m_nObjectListSize; ++i)
        {
            auto *obj = reinterpret_cast<LTObjectCompat *>(scene->m_pObjectList[i]);
            if (!obj || obj->m_nObjectType != OT_MODEL)
                continue;

            auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
            if (IsLocalThirdPersonParent(scene, inst))
                continue;
            const uint32 effectiveFlags = ABCModelRenderer::Instance().EffectiveFlags(scene, inst);
            if (effectiveFlags & FLAG_REALLYCLOSE)
            {
                ++sceneRCCount;
                collect(inst);
            }
        }
    }

    static uint32 lastSceneRC = 0xFFFFFFFFu;
    if (LogIsSessionEnabled() && (lastSceneRC != sceneRCCount))
    {
        lastSceneRC = sceneRCCount;
        LOG_SESSION("Model3D SCENE-RC objects=%d rcModels=%u", scene->m_nObjectListSize, sceneRCCount);
    }

    uint32 rendered = 0;
    uint32 reallyCloseRendered = 0;
    const uint64_t trisBefore = ABCModelRenderer::Instance().TrianglesDrawn();

    std::vector<ModelInstanceCompat *> opaqueModels;
    std::vector<ModelInstanceCompat *> chromaModels;
    std::vector<ModelInstanceCompat *> translucentModels;
    opaqueModels.reserve(normalModels.size());
    chromaModels.reserve(normalModels.size());
    translucentModels.reserve(normalModels.size());

    for (ModelInstanceCompat *inst : normalModels)
    {
        if (!inst)
            continue;
        const LTObjectCompat &o = inst->m_Base;
        // Exact classifier in d3d.ren at 0x10024CEB: object alpha first,
        // then FLAG2_CHROMAKEY. Additive/multiply are material states, not a
        // reason to move an alpha-255 model to VS_MODELS_TRANSLUCENT.
        const bool translucent = (o.m_nColorA < 255);
        const bool chroma = (o.m_dwFlags2 & FLAG2_CHROMAKEY) != 0;
        if (translucent)
            translucentModels.push_back(inst);
        else if (chroma)
            chromaModels.push_back(inst);
        else
            opaqueModels.push_back(inst);
    }

    RendererCore::Instance().PerfSetSceneObjectCounts(
        count, static_cast<uint32_t>(opaqueModels.size()), static_cast<uint32_t>(chromaModels.size()),
        static_cast<uint32_t>(translucentModels.size()), static_cast<uint32_t>(reallyCloseModels.size()),
        translucentWorldModels, WorldRenderer::Instance().PVS().GetSpriteCount(),
        WorldRenderer::Instance().PVS().GetParticleSystemCount(), WorldRenderer::Instance().PVS().GetPolyGridCount(),
        WorldRenderer::Instance().PVS().GetLineSystemCount(), WorldRenderer::Instance().PVS().GetCanvasCount());
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::ModelPrep, prepStart);

    // d3d.ren 0x1002873D executes the solid Canvas flush before the later
    // model/translucent phases.  Canvas callbacks can change primitive state,
    // so re-establish the model pipeline immediately afterwards.
    const int64_t solidFxStart = RendererCore::Instance().PerfTimingBegin();
    RenderSolidCanvasesFromPVS(scene);
    // Retail has a distinct VS_POLYGRIDS bucket.  Solid PolyGrids are not
    // members of the shared distance-sorted translucent object list.
    RenderSolidPolyGridsFromPVS(scene);
    SetupScenePipeline(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::SolidFx, solidFxStart);

    // Simple Talon-style character blob shadows are a separate ground pass.
    // Only character-body ABCs participate; attachments, props, pickups, menus
    // and ReallyClose/view models are deliberately excluded. Render them after
    // the opaque world and before the actor body so feet naturally cover them.
    const int64_t shadowStart = RendererCore::Instance().PerfTimingBegin();
    ABCModelRenderer::Instance().RenderShadows(scene, normalModels, attachmentSet);
    SetupScenePipeline(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Shadows, shadowStart);

    // d3d.ren's object flush (0x10028660) is phase-based:
    // VS_WORLDMODELS -> VS_MODELS -> WORLDMODELS_CHROMAKEY ->
    // MODELS_CHROMAKEY -> deferred translucent queue -> SPRITES_NOZ.
    // WorldRenderer::RenderScene already emitted VS_WORLDMODELS (opaque), so emit
    // the matching opaque model phase now.
    const int64_t modelStart = RendererCore::Instance().PerfTimingBegin();
    for (ModelInstanceCompat *inst : opaqueModels)
    {
        if (RenderModel(scene, inst))
            ++rendered;
    }
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Models, modelStart);

    // Chromakey worldmodels precede chromakey models in stock Talon.
    const int64_t worldModelStart = RendererCore::Instance().PerfTimingBegin();
    WorldRenderer::Instance().WorldModels().RenderDeferred(scene, WorldModelPhase::ChromaKey);
    SetupScenePipeline(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::WorldModels, worldModelStart);
    const int64_t chromaModelStart = RendererCore::Instance().PerfTimingBegin();
    for (ModelInstanceCompat *inst : chromaModels)
    {
        if (RenderModel(scene, inst))
            ++rendered;
    }
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Models, chromaModelStart);

    const int64_t opaqueQualityStart = RendererCore::Instance().PerfTimingBegin();
    GUIQuality::Instance().ApplyOpaqueScene(scene);
    SetupScenePipeline(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Quality, opaqueQualityStart);

    // d3d.ren does NOT flush translucent WorldModels here. They are
    // contributed to the same sorted list handled below.

    // d3d.ren does not directly draw VS_MODELS_TRANSLUCENT or VS_SPRITES here;
    // each contributes a callback/object pair to the same sorted translucent
    // list, which is then flushed back-to-front.  Mirror that behavior for the
    // object classes implemented by this renderer.
    const int64_t translucentStart = RendererCore::Instance().PerfTimingBegin();
    RenderStockTranslucentStage(scene, translucentModels);
    rendered += static_cast<uint32>(translucentModels.size());
    ABCModelRenderer::Instance().BindPipeline();
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::Translucent, translucentStart);

    // VS_SPRITES_NOZ is a dedicated pass after the sorted translucent list.
    const int64_t noZStart = RendererCore::Instance().PerfTimingBegin();
    RenderNoZSpritesFromPVS(scene);
    ABCModelRenderer::Instance().BindPipeline();
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::NoZ, noZStart);

    static int phaseLogBudget = 32;
    if (LogIsSessionEnabled() && ((phaseLogBudget > 0 && phaseLogBudget--)))
        LOG_SESSION("Model3D STOCK-PHASE opaque=%u chroma=%u translucent=%u rc=%u",
                    unsigned(opaqueModels.size()), unsigned(chromaModels.size()),
                    unsigned(translucentModels.size()), unsigned(reallyCloseModels.size()));

    // d3d.ren d3d_SetReallyClose() does NOT clear depth. It keeps the world
    // Z-buffer and changes only the viewport MinZ/MaxZ to 0..0.1, then uses
    // the dedicated ReallyClose projection.
    const int64_t reallyCloseStart = RendererCore::Instance().PerfTimingBegin();
    if (!reallyCloseModels.empty())
    {
        GLStateEnable(GL_DEPTH_TEST);
        GLStateDepthFunc(GL_LEQUAL);
        GLStateDepthMask(GL_TRUE);
        GLStateDepthRange(0.0, 0.1);

        for (ModelInstanceCompat *inst : reallyCloseModels)
        {
            if (RenderModel(scene, inst))
            {
                ++rendered;
                ++reallyCloseRendered;
            }
        }

        RenderVisibleEffectsFromPVS(scene, true);
        GLStateDepthRange(0.0, 1.0);
        ABCModelRenderer::Instance().BindPipeline();
    }
    else
    {
        bool haveRCFx = false;
        for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetSpriteCount() && !haveRCFx; ++i)
        {
            auto *o = reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetSprite(i));
            haveRCFx = o && (o->m_dwFlags & FLAG_REALLYCLOSE);
        }
        for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetParticleSystemCount() && !haveRCFx; ++i)
        {
            auto *o = reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetParticleSystem(i));
            haveRCFx = o && (o->m_dwFlags & FLAG_REALLYCLOSE);
        }
        for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetPolyGridCount() && !haveRCFx; ++i)
        {
            auto *o = reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetPolyGrid(i));
            haveRCFx = o && (o->m_dwFlags & FLAG_REALLYCLOSE);
        }
        for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetLineSystemCount() && !haveRCFx; ++i)
        {
            auto *o = reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetLineSystem(i));
            haveRCFx = o && (o->m_dwFlags & FLAG_REALLYCLOSE);
        }
        for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetCanvasCount() && !haveRCFx; ++i)
        {
            auto *c = WorldRenderer::Instance().PVS().GetCanvas(i);
            haveRCFx = c && !IsStockSolidCanvas(c) && (c->m_Base.m_dwFlags & FLAG_REALLYCLOSE);
        }
        if (haveRCFx)
        {
            GLStateEnable(GL_DEPTH_TEST);
            GLStateDepthFunc(GL_LEQUAL);
            GLStateDepthRange(0.0, 0.1);
            RenderVisibleEffectsFromPVS(scene, true);
            GLStateDepthRange(0.0, 1.0);
            ABCModelRenderer::Instance().BindPipeline();
        }
    }
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::ReallyClose, reallyCloseStart);

    static uint32 lastVisible = 0xFFFFFFFFu;
    static uint32 lastRendered = 0xFFFFFFFFu;
    static uint32 lastRC = 0xFFFFFFFFu;
    if (LogIsSessionEnabled() && (lastVisible != count || lastRendered != rendered || lastRC != reallyCloseRendered))
    {
        lastVisible = count;
        lastRendered = rendered;
        lastRC = reallyCloseRendered;
        LOG_SESSION("Model3D WORLD PVS visible=%u submitted=%u rendered=%u normal=%u reallyClose=%u tris=%llu",
                    count, static_cast<unsigned>(pvsModels.size()), rendered,
                    static_cast<unsigned>(normalModels.size()), reallyCloseRendered,
                    static_cast<unsigned long long>(ABCModelRenderer::Instance().TrianglesDrawn() - trisBefore));
    }
}

static bool IsTalonLoadingInterfaceModelName(const char *filename)
{
    if (!filename || !*filename)
        return false;

    // Known AVP2 loading-screen model families observed in the Talon client:
    //   LM_*  marine loading UI
    //   LA_*  alien loading UI
    //   LP_*  predator loading UI (same naming convention; keep parity)
    // Some alien overlay pieces use A_FOG*.ABC rather than LA_*.
    const char *base = filename;
    if (const char *slash = wp_strrchr_sep(filename))
        base = slash + 1;
    if (const char *slash2 = strrchr(base, '/'))
        base = slash2 + 1;

    return _strnicmp(base, "LM_", 3) == 0 ||
           _strnicmp(base, "LA_", 3) == 0 ||
           _strnicmp(base, "LP_", 3) == 0 ||
           _strnicmp(base, "A_FOG", 5) == 0;
}

bool SceneRenderer::IsTalonLoadingObjectList(const SceneDesc *scene) const
{
    if (!scene || scene->m_nDrawMode != DRAWMODE_OBJECTLIST ||
        !scene->m_pObjectList || scene->m_nObjectListSize <= 0)
        return false;

    unsigned visibleModels = 0;
    unsigned reallyCloseModels = 0;
    unsigned visibleSprites = 0;
    bool hasKnownLoadingModel = false;

    for (int i = 0; i < scene->m_nObjectListSize; ++i)
    {
        auto *obj = reinterpret_cast<LTObjectCompat *>(scene->m_pObjectList[i]);
        if (!obj || !(obj->m_dwFlags & FLAG_VISIBLE))
            continue;

        if (obj->m_nObjectType == OT_MODEL)
        {
            ++visibleModels;
            if (obj->m_dwFlags & FLAG_REALLYCLOSE)
                ++reallyCloseModels;

            auto *inst = reinterpret_cast<ModelInstanceCompat *>(obj);
            Model *model = GetModelFromInstance(inst);
            if (model && IsTalonLoadingInterfaceModelName(model->m_szFilename))
                hasKnownLoadingModel = true;
        }
        else if (obj->m_nObjectType == OT_SPRITE)
        {
            ++visibleSprites;
        }
    }

    if (!visibleModels || !visibleSprites || reallyCloseModels != visibleModels)
        return false;

    // Prefer asset identity.  The structural fallback covers loading-screen
    // variants whose model family has not yet appeared in our traces.  Normal
    // AVP2 menu object lists use FarZ=10000; loading lists in stock
    // Talon use 30000/45000/100000 and have 3 object slots for models + 2
    // visible sprites (one model slot may be invisible, yielding 2 visible).
    const bool loadingStructure =
        scene->m_fFarZ >= 20000.0f &&
        scene->m_nObjectListSize == 6 &&
        visibleModels >= 2 && visibleModels <= 3 &&
        visibleSprites == 2;

    return hasKnownLoadingModel || loadingStructure;
}

static void RenderObjectListLikeTalon(SceneDesc *scene)
{
    if (!scene->m_pObjectList || scene->m_nObjectListSize <= 0)
        return;

    std::vector<ModelInstanceCompat *> models;
    std::vector<ParticleSystemCompat *> particleSystems;
    std::vector<PolyGridCompat *> polyGrids;
    std::vector<LineSystemCompat *> lineSystems;
    std::vector<CanvasCompat *> canvases;
    std::vector<QueuedSprite> translucentSprites;
    std::vector<QueuedSprite> noZSprites;

    models.reserve(scene->m_nObjectListSize);
    particleSystems.reserve(scene->m_nObjectListSize);
    polyGrids.reserve(scene->m_nObjectListSize);
    lineSystems.reserve(scene->m_nObjectListSize);
    canvases.reserve(scene->m_nObjectListSize);
    translucentSprites.reserve(scene->m_nObjectListSize);
    noZSprites.reserve(scene->m_nObjectListSize);

    for (int i = 0; i < scene->m_nObjectListSize; ++i)
    {
        auto *obj = reinterpret_cast<LTObjectCompat *>(scene->m_pObjectList[i]);
        if (!obj || !(obj->m_dwFlags & FLAG_VISIBLE))
            continue;

        if (obj->m_nObjectType == OT_MODEL)
        {
            models.push_back(reinterpret_cast<ModelInstanceCompat *>(obj));
        }
        else if (obj->m_nObjectType == OT_PARTICLESYSTEM)
        {
            particleSystems.push_back(reinterpret_cast<ParticleSystemCompat *>(obj));
        }
        else if (obj->m_nObjectType == OT_POLYGRID)
        {
            polyGrids.push_back(reinterpret_cast<PolyGridCompat *>(obj));
        }
        else if (obj->m_nObjectType == OT_LINESYSTEM)
        {
            lineSystems.push_back(reinterpret_cast<LineSystemCompat *>(obj));
        }
        else if (obj->m_nObjectType == OT_CANVAS)
        {
            canvases.push_back(reinterpret_cast<CanvasCompat *>(obj));
        }
        else if (obj->m_nObjectType == OT_SPRITE)
        {
            QueuedSprite q{};
            q.sprite = reinterpret_cast<SpriteInstanceCompat *>(obj);
            q.distanceSq = SpriteDistanceSq(scene, *obj);
            q.radius = obj->m_fRadius;
            q.specialBlendBits = obj->m_dwFlags2 & (FLAG2_ADDITIVE | FLAG2_MULTIPLY);
            q.reallyClose = (obj->m_dwFlags & FLAG_REALLYCLOSE) != 0;
            q.sourceIndex = i;

            if (obj->m_dwFlags & FLAG_SPRITE_NOZ)
                noZSprites.push_back(q);
            else
                translucentSprites.push_back(q);
        }
    }

    // Menu/object-list composition: establish the authored sprite/background
    // stack first, then render the 3D model layer over it. RenderDoc confirms
    // the model-first ordering was wrong for these interface scenes.
    std::stable_sort(translucentSprites.begin(), translucentSprites.end(), SpriteQueueBefore);

    static int orderLogBudget = 4;
    const bool logOrder = LogIsSessionEnabled() && orderLogBudget > 0;
    if (logOrder)
    {
        LOG_SESSION("Sprite3D QUEUE translucent=%u noZ=%u models=%u",
                    static_cast<unsigned>(translucentSprites.size()),
                    static_cast<unsigned>(noZSprites.size()),
                    static_cast<unsigned>(models.size()));
    }

    // Stock Talon object-list phase ordering applies to the whole interface,
    // not to a particular model filename family.  The d3d.ren object flush
    // draws alpha-255 model objects in the solid-model phase before sprites
    // are queued into the translucent stage.  Alpha<255 models are deferred
    // to the later translucent-model phase.
    //
    // This is the same ordering that fixed the loading weapon UI, but it also
    // correctly describes ordinary menu compositions such as:
    //   MENU_DROPSHIP (opaque) -> menu sprites -> DROPSHIPFLARE (translucent)
    //   SP_PREDATOR   (opaque) -> menu sprites -> SP_LASER      (translucent)
    //
    // RenderObjectListLikeTalon is only used for DRAWMODE_OBJECTLIST, so no
    // asset-name, FarZ, or loading-screen heuristic belongs here.
    for (CanvasCompat *canvas : canvases)
    {
        if (canvas && IsStockSolidCanvas(canvas))
            FXRenderer::Instance().RenderCanvas(scene, canvas);
    }
    ABCModelRenderer::Instance().BindPipeline();

    unsigned opaqueFirst = 0;
    for (ModelInstanceCompat *model : models)
    {
        if (!model || model->m_Base.m_nColorA < 255)
            continue;
        RenderModel(scene, model);
        ABCModelRenderer::Instance().BindPipeline();
        ++opaqueFirst;
    }

    static int talonOrderLogBudget = 48;
    if (LogIsSessionEnabled() && ((talonOrderLogBudget > 0 && talonOrderLogBudget--)))
        LOG_SESSION("TALON-OBJECTLIST-ORDER global=1 far=%.1f opaqueModelsFirst=%u spritesNext=%u translucentModelsLast=%u noZLast=%u",
                    scene->m_fFarZ, opaqueFirst,
                    static_cast<unsigned>(translucentSprites.size()),
                    static_cast<unsigned>(models.size() - opaqueFirst),
                    static_cast<unsigned>(noZSprites.size()));

    for (size_t i = 0; i < translucentSprites.size(); ++i)
    {
        const QueuedSprite &q = translucentSprites[i];

        if (logOrder)
        {
            const LTObjectCompat &o = q.sprite->m_Base;
            LOG_SESSION("  SPRQ[%u] src=%d RC=%d dist2=%.2f z=%.2f radius=%.2f flags=%08X flags2=%08X",
                        static_cast<unsigned>(i), q.sourceIndex, q.reallyClose ? 1 : 0,
                        q.distanceSq, o.m_vPos.z, q.radius, o.m_dwFlags, o.m_dwFlags2);
        }

        SpriteRenderer::Instance().Render(scene, q.sprite);
        ABCModelRenderer::Instance().BindPipeline();
    }

    // Translucent interface FX participate with the sprite/background layer.
    for (ParticleSystemCompat *system : particleSystems)
        FXRenderer::Instance().RenderParticleSystem(scene, system);

    for (PolyGridCompat *grid : polyGrids)
        FXRenderer::Instance().RenderPolyGrid(scene, grid);

    for (LineSystemCompat *system : lineSystems)
        FXRenderer::Instance().RenderLineSystem(scene, system);

    for (CanvasCompat *canvas : canvases)
    {
        if (canvas && !IsStockSolidCanvas(canvas))
            FXRenderer::Instance().RenderCanvas(scene, canvas);
    }

    // Stock Talon sends alpha<255 models to the later translucent-model
    // phase for every object-list scene.  Keep their blend/depth behavior
    // separate from the alpha-255 model phase above.
    for (ModelInstanceCompat *model : models)
    {
        if (!model || model->m_Base.m_nColorA == 255)
            continue;
        RenderModel(scene, model, true);
        ABCModelRenderer::Instance().BindPipeline();
    }

    // Reference renderer has a dedicated d3d_DrawNoZSprites() pass after the
    // sorted translucent queue.
    // No-Z sprites do not need distance sorting for depth correctness; keep
    // source order to stay deterministic.
    std::stable_sort(noZSprites.begin(), noZSprites.end(),
                     [](const QueuedSprite &a, const QueuedSprite &b)
                     {
                         return a.sourceIndex < b.sourceIndex;
                     });

    for (const QueuedSprite &q : noZSprites)
    {
        SpriteRenderer::Instance().Render(scene, q.sprite);
        ABCModelRenderer::Instance().BindPipeline();
    }

    if (logOrder)
        --orderLogBudget;
}

struct VisibleEffectItem
{
    LTObjectCompat *obj = nullptr;
    float dist2 = 0.0f;
};

static void RenderVisibleEffectsFromPVS(SceneDesc *scene, bool reallyClosePass)
{
    if (!scene)
        return;

    std::vector<VisibleEffectItem> items;
    items.reserve(WorldRenderer::Instance().PVS().GetSpriteCount() + WorldRenderer::Instance().PVS().GetParticleSystemCount() +
                  WorldRenderer::Instance().PVS().GetPolyGridCount() + WorldRenderer::Instance().PVS().GetLineSystemCount() + WorldRenderer::Instance().PVS().GetCanvasCount());

    auto add = [&](LTObjectCompat *o)
    {
        if (!o || !(o->m_dwFlags & FLAG_VISIBLE))
            return;
        const bool rc = (o->m_dwFlags & FLAG_REALLYCLOSE) != 0;
        if (rc != reallyClosePass)
            return;
        float d2;
        if (o->m_dwFlags & FLAG_REALLYCLOSE)
            d2 = o->m_vPos.x * o->m_vPos.x + o->m_vPos.y * o->m_vPos.y + o->m_vPos.z * o->m_vPos.z;
        else
        {
            const float x = o->m_vPos.x - scene->m_vPos.x;
            const float y = o->m_vPos.y - scene->m_vPos.y;
            const float z = o->m_vPos.z - scene->m_vPos.z;
            d2 = x * x + y * y + z * z;
        }
        items.push_back({o, d2});
    };

    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetSpriteCount(); ++i)
        add(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetSprite(i)));
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetParticleSystemCount(); ++i)
        add(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetParticleSystem(i)));
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetPolyGridCount(); ++i)
        add(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetPolyGrid(i)));
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetLineSystemCount(); ++i)
        add(reinterpret_cast<LTObjectCompat *>(WorldRenderer::Instance().PVS().GetLineSystem(i)));
    for (uint32 i = 0; i < WorldRenderer::Instance().PVS().GetCanvasCount(); ++i)
    {
        CanvasCompat *c = WorldRenderer::Instance().PVS().GetCanvas(i);
        if (c && !IsStockSolidCanvas(c))
            add(&c->m_Base);
    }

    // Talon's translucent object list is back-to-front across object classes.
    std::stable_sort(items.begin(), items.end(), [](const auto &a, const auto &b)
                     { return a.dist2 > b.dist2; });

    uint32 sp = 0, ps = 0, pg = 0, ls = 0, cv = 0;
    for (const VisibleEffectItem &it : items)
    {
        switch (it.obj->m_nObjectType)
        {
        case OT_SPRITE:
            SpriteRenderer::Instance().Render(scene, reinterpret_cast<SpriteInstanceCompat *>(it.obj));
            ++sp;
            break;
        case OT_PARTICLESYSTEM:
            FXRenderer::Instance().RenderParticleSystem(scene, reinterpret_cast<ParticleSystemCompat *>(it.obj));
            ++ps;
            break;
        case OT_POLYGRID:
            FXRenderer::Instance().RenderPolyGrid(scene, reinterpret_cast<PolyGridCompat *>(it.obj));
            ++pg;
            break;
        case OT_LINESYSTEM:
            FXRenderer::Instance().RenderLineSystem(scene, reinterpret_cast<LineSystemCompat *>(it.obj));
            ++ls;
            break;
        case OT_CANVAS:
            FXRenderer::Instance().RenderCanvas(scene, reinterpret_cast<CanvasCompat *>(it.obj));
            ++cv;
            break;
        default:
            break;
        }
        ABCModelRenderer::Instance().BindPipeline();
    }

    static uint32 lastSp = ~0u, lastPs = ~0u, lastPg = ~0u, lastLs = ~0u, lastCv = ~0u;
    if (LogIsSessionEnabled() && (lastSp != sp || lastPs != ps || lastPg != pg || lastLs != ls || lastCv != cv))
    {
        lastSp = sp;
        lastPs = ps;
        lastPg = pg;
        lastLs = ls;
        lastCv = cv;
        LOG_SESSION("FX3D %s QUEUE sprites=%u particles=%u polygrids=%u lines=%u canvases=%u total=%u", reallyClosePass ? "RC" : "WORLD", sp, ps, pg, ls, cv, unsigned(items.size()));
    }
}

int SceneRenderer::RenderScene(SceneDesc *scene)
{
    if (!scene)
        return RENDER_OK;

    const uint64_t frameTrisStart = ABCModelRenderer::Instance().TrianglesDrawn();
    const uint64_t frameModelsStart = ABCModelRenderer::Instance().ModelsDrawn();
    ++g_sceneCount;
    g_loadingObjectList = LogIsSessionEnabled() && IsTalonLoadingObjectList(scene);
    LogSceneTypes(scene);

    if (scene->m_nDrawMode != DRAWMODE_OBJECTLIST)
    {
        const int64_t worldStart = RendererCore::Instance().PerfTimingBegin();
        const int result = WorldRenderer::Instance().RenderScene(scene);
        RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::World, worldStart);

        RenderVisibleSceneObjects(scene);

        GLStateDisable(GL_SCISSOR_TEST);
        glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
        GLStateDisable(GL_DEPTH_TEST);
        g_lastFrameModelTris = ABCModelRenderer::Instance().TrianglesDrawn() - frameTrisStart;
        g_lastFrameModelsDrawn = static_cast<uint32>(ABCModelRenderer::Instance().ModelsDrawn() - frameModelsStart);
        return result;
    }

    Renderer2D::Instance().Flush();

    SetupScenePipeline(scene);
    GLStateEnable(GL_BLEND);
    GLStateBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int64_t objectListStart = RendererCore::Instance().PerfTimingBegin();
    RenderObjectListLikeTalon(scene);
    RendererCore::Instance().PerfTimingEnd(PerfTimingSystem::ObjectList, objectListStart);

    GLStateDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, RendererCore::Instance().Width(), RendererCore::Instance().Height());
    GLStateDisable(GL_DEPTH_TEST);

    g_lastFrameModelTris = ABCModelRenderer::Instance().TrianglesDrawn() - frameTrisStart;
    g_lastFrameModelsDrawn = static_cast<uint32>(ABCModelRenderer::Instance().ModelsDrawn() - frameModelsStart);

    const ULONGLONG now = GetTickCount64();
    if (g_lastStats == 0 || now - g_lastStats >= 1000)
    {
        if (LogIsSessionEnabled())
        {
            uint64_t spriteCount = 0;
            uint64_t spriteTris = 0;
            SpriteRenderer::Instance().GetStats(spriteCount, spriteTris);

            LOG_SESSION("3DPERF[1s] scenes=%llu models=%llu modelTris=%llu sprites=%llu spriteTris=%llu",
                        static_cast<unsigned long long>(g_sceneCount),
                        static_cast<unsigned long long>(ABCModelRenderer::Instance().ModelsDrawn()),
                        static_cast<unsigned long long>(ABCModelRenderer::Instance().TrianglesDrawn()),
                        static_cast<unsigned long long>(spriteCount),
                        static_cast<unsigned long long>(spriteTris));
        }

        g_sceneCount = 0;
        ABCModelRenderer::Instance().ResetStats();
        SpriteRenderer::Instance().ResetStats();
        g_lastStats = now;
    }

    return RENDER_OK;
}


SceneRenderer &SceneRenderer::Instance()
{
    static SceneRenderer renderer;
    return renderer;
}

uint64_t SceneRenderer::LastFrameModelTriangles() const { return g_lastFrameModelTris; }
uint32 SceneRenderer::LastFrameModelsDrawn() const { return g_lastFrameModelsDrawn; }

bool SceneRenderer::Init()
{
    return ABCModelRenderer::Instance().Init() &&
           SpriteRenderer::Instance().Init() &&
           FXRenderer::Instance().Init() &&
           WorldRenderer::Instance().Init();
}

void SceneRenderer::Term()
{
    WorldRenderer::Instance().Term();
    FXRenderer::Instance().Term();
    SpriteRenderer::Instance().Term();
    ABCModelRenderer::Instance().Term();
    ABCModelRenderer::Instance().ResetStats();
    g_sceneCount = g_lastFrameModelTris = g_lastStats = 0;
    g_lastFrameModelsDrawn = 0;
    g_loadingObjectList = false;
}

void SceneRenderer::SetRenderStruct(RenderStruct *rs)
{
    m_renderStruct = rs;
    ABCModelRenderer::Instance().SetRenderStruct(rs);
}
