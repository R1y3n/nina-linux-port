#pragma once
#include <windows.h>
#include <cstdint>
#include <cstddef>
#include <cmath>
#include <algorithm>

using int8 = char;
using uint8 = unsigned char;
using int16 = short;
using uint16 = unsigned short;
using int32 = int;
using uint32 = unsigned int;

using LTBOOL = uint32;
using LTFLOAT = float;
using LTRESULT = uint32;
using HLTCOLOR = uint32;
using HLTBUFFER = void *;
using HLTPARAM = void *;

constexpr LTBOOL LTFALSE = 0;
constexpr LTBOOL LTTRUE = 1;

constexpr int LTRENDER_VERSION = 3421; // 0x0D5D
constexpr int RENDER_OK = 0;
constexpr int RENDER_ERROR = 1;

constexpr uint32 CLEARSCREEN_SCREEN = 1;
constexpr uint32 CLEARSCREEN_RENDER = 2;
constexpr uint32 BLIT_TRANSPARENT = 1;

struct LTObject;
struct Attachment;
struct SharedTexture;
struct TextureData;
struct MainWorld;
struct RenderContext
{
    uint32 m_dwData_0;
    uint32 m_dwData_4;
    MainWorld *m_pMainWorld;
    uint16 m_wCurFrameCode;
    uint16 m_wPadding;
};

struct RenderContextInit
{
    MainWorld *m_pMainWorld;
};

union GenericColor
{
    uint32 dwVal;
    uint16 wVal;
    uint8 bVal;
};

struct LTVector
{
    float x, y, z;
    LTVector() : x(0), y(0), z(0) {}

    LTVector(float x, float y, float z) : x(x), y(y), z(z) {}

    LTVector operator+(const LTVector &other) const
    {
        return LTVector(x + other.x, y + other.y, z + other.z);
    }

    LTVector operator-(const LTVector &other) const
    {
        return LTVector(x - other.x, y - other.y, z - other.z);
    }

    LTVector operator*(float scalar) const
    {
        return LTVector(x * scalar, y * scalar, z * scalar);
    }
    LTVector operator*(const LTVector &other) const
    {
        return LTVector(x * other.x, y * other.y, z * other.z);
    }

    float dot(const LTVector &other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    LTVector cross(const LTVector &other) const
    {
        return LTVector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    LTVector normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length <= 1e-8f)
        {
            return LTVector(0, 0, 0);
        }
        return LTVector(x / length, y / length, z / length);
    }

    LTVector scale(float scalar) const
    {
        return LTVector(x * scalar, y * scalar, z * scalar);
    }

    float length() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    float Clamp(float v) const
    {
        return std::max(0.0f, std::min(1.0f, v));
    }

    LTVector Clamp() const
    {
        return LTVector(Clamp(x), Clamp(y), Clamp(z));
    }

    LTVector operator/(float scalar) const
    {
        return LTVector(x / scalar, y / scalar, z / scalar);
    }

    LTVector &operator+=(const LTVector &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    LTVector &operator-=(const LTVector &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    LTVector &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    LTVector &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    LTVector Rotate(const LTVector &other) const
    {
        return LTVector(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x);
    }

    LTVector Lerp(const LTVector &other, float t) const
    {
        return LTVector(
            x + (other.x - x) * t,
            y + (other.y - y) * t,
            z + (other.z - z) * t);
    }
};

struct LTFloatPt
{
    float x, y;
    LTFloatPt() : x(0), y(0) {}

    LTFloatPt(float x, float y) : x(x), y(y) {}

    LTFloatPt operator+(const LTFloatPt &other) const
    {
        return LTFloatPt(x + other.x, y + other.y);
    }

    LTFloatPt operator-(const LTFloatPt &other) const
    {
        return LTFloatPt(x - other.x, y - other.y);
    }

    LTFloatPt operator*(float scalar) const
    {
        return LTFloatPt(x * scalar, y * scalar);
    }
};

struct PGColor
{
    float x, y, z; // RGB 0-255
    float a;       // Alpha 0-255
    PGColor() : x(0), y(0), z(0), a(0) {}

    PGColor(float x, float y, float z, float a) : x(x), y(y), z(z), a(a) {}
    PGColor operator+(const PGColor &other) const
    {
        return PGColor(x + other.x, y + other.y, z + other.z, a + other.a);
    }

    PGColor operator-(const PGColor &other) const
    {
        return PGColor(x - other.x, y - other.y, z - other.z, a - other.a);
    }

    PGColor operator*(float scalar) const
    {
        return PGColor(x * scalar, y * scalar, z * scalar, a * scalar);
    }
    PGColor operator/(float scalar) const
    {
        return PGColor(x / scalar, y / scalar, z / scalar, a / scalar);
    }
    PGColor &operator+=(const PGColor &other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        a += other.a;
        return *this;
    }

    PGColor &operator-=(const PGColor &other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        a -= other.a;
        return *this;
    }

    PGColor &operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        a *= scalar;
        return *this;
    }

    PGColor &operator/=(float scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        a /= scalar;
        return *this;
    }
};

struct LTPlaneCompat
{
    LTVector m_vNormal;
    float m_fDist;
};

struct LTRotation
{
    float x, y, z, w;

    LTRotation()
    {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
        w = 1.0f;
    }

    LTRotation(float x, float y, float z, float w)
    {
        this->x = x;
        this->y = y;
        this->z = z;
        this->w = w;
    }

    LTRotation(const LTRotation &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
    }

    LTRotation &operator=(const LTRotation &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        w = other.w;
        return *this;
    }

    LTRotation Normalize() const
    {
        float d = std::sqrt(x * x + y * y + z * z + w * w);
        if (d <= 1e-8f)
            return LTRotation(0, 0, 0, 1);
        return LTRotation(x / d, y / d, z / d, w / d);
    }

    LTRotation Conjugate() const
    {
        return LTRotation(-x, -y, -z, w);
    }

    LTVector Rotate(const LTVector &v) const
    {
        LTRotation q = Normalize();
        LTVector u{q.x, q.y, q.z};
        const float s = q.w;

        const float dotUV = u.x * v.x + u.y * v.y + u.z * v.z;
        const float dotUU = u.x * u.x + u.y * u.y + u.z * u.z;

        LTVector cross{
            u.y * v.z - u.z * v.y,
            u.z * v.x - u.x * v.z,
            u.x * v.y - u.y * v.x};

        return LTVector{
            2.0f * dotUV * u.x + (s * s - dotUU) * v.x + 2.0f * s * cross.x,
            2.0f * dotUV * u.y + (s * s - dotUU) * v.y + 2.0f * s * cross.y,
            2.0f * dotUV * u.z + (s * s - dotUU) * v.z + 2.0f * s * cross.z};
    }
};

struct Attachment
{
    LTVector m_vOffsetPos;   // 0
    LTRotation m_rOffsetRot; // 12
    uint16 m_nChildID;       // 28
    uint16 m_nParentID;      // 30
    uint32 m_iSocket;        // 32
    Attachment *m_pNext;     // 36
};
static_assert(offsetof(Attachment, m_nChildID) == 28, "Attachment child id offset mismatch");
static_assert(offsetof(Attachment, m_iSocket) == 32, "Attachment socket offset mismatch");
static_assert(offsetof(Attachment, m_pNext) == 36, "Attachment next offset mismatch");

struct LTRect
{
    int m_nLeft;
    int m_nTop;
    int m_nRight;
    int m_nBottom;
};

struct LTWarpPt
{
    float m_fSourceX;
    float m_fSourceY;
    float m_fDestX;
    float m_fDestY;
};

enum LTSurfaceBlend
{
    LTSURFACEBLEND_ALPHA = 0,
    LTSURFACEBLEND_SOLID = 1,
    LTSURFACEBLEND_ADD,
    LTSURFACEBLEND_MULTIPLY,
    LTSURFACEBLEND_MULTIPLY2,
    LTSURFACEBLEND_MASK,
    LTSURFACEBLEND_MASKADD
};

enum BPPIdent
{
    BPP_8P = 0,
    BPP_8,
    BPP_16,
    BPP_32,
    BPP_S3TC_DXT1,
    BPP_S3TC_DXT3,
    BPP_S3TC_DXT5,
    BPP_32P,
    BPP_24,
    NUM_BIT_TYPES
};

enum ColorPlanes
{
    CP_ALPHA = 0,
    CP_RED = 1,
    CP_GREEN = 2,
    CP_BLUE = 3,
    NUM_COLORPLANES = 4
};

struct PFormat
{
    uint32 m_dwVTable;
    BPPIdent m_eType;
    uint32 m_adwMasks[NUM_COLORPLANES];
    uint32 m_adwBits[NUM_COLORPLANES];
    uint32 m_adwFirstBits[NUM_COLORPLANES];
};

struct WorldBspCompat;
struct SurfaceCompat;

struct CommonEffectCompat
{
    LTVector m_vO;
    LTVector m_vP;
    LTVector m_vQ;
    LTVector m_vData36;
    float m_fParam1;
    float m_fParam2;
    float m_fParam3;
    float m_fParam4;
};
static_assert(sizeof(CommonEffectCompat) == 64, "CommonEffectCompat size mismatch");

struct SurfaceEffectCompat
{
    WorldBspCompat *m_pWorldBsp;
    SurfaceCompat *m_pSurface;
    CommonEffectCompat *m_pCommonEffect;
    void *m_pDesc;
    SurfaceEffectCompat *m_pPrev;
};
static_assert(sizeof(SurfaceEffectCompat) == 20, "SurfaceEffectCompat size mismatch");

template <typename T>
struct CMoArrayDefaultCacheCompat
{
    uint32 *m_pVTable;
    T *m_pArray;
    uint32 m_dwElements;
    uint32 m_dwCacheSize;
    uint32 m_dwWantedCache;
};

// Engine lifetime-notification nexus. Its leech nodes dispatch callbacks on
// owner destruction; their full layout is not modeled here.
struct NexusCompat
{
    void *m_pLeechHead; // 0
    void *m_pData;      // 4 - owner data, initialized to the Surface for surfaces
};
static_assert(sizeof(NexusCompat) == 8, "NexusCompat size mismatch");
static_assert(offsetof(NexusCompat, m_pLeechHead) == 0, "Nexus leech head offset mismatch");
static_assert(offsetof(NexusCompat, m_pData) == 4, "Nexus owner data offset mismatch");

// Verified against Talon's surface constructor/loader; see
// docs/surface_layout_trace.md for binary addresses and remaining uncertainties.
struct SurfaceCompat
{
    LTVector m_vO;              // 0
    LTVector m_vP;              // 12
    LTVector m_vQ;              // 24
    NexusCompat m_Nexus;        // 36 - initialized with m_pData = this surface
    SharedTexture *m_pTexture;  // 44
    uint32 m_dwFlags;           // 48
    uint16 m_wTextureFlags;     // 52
    uint16 m_wTexture;          // 54
    uint16 m_wPoly;             // 56
    uint16 m_wPortalIDAndFlags; // 58 - initialized to 0x7FFF
    uint8 m_nData_60;           // 60 - zeroed, then loaded from DAT; meaning unknown
    uint8 m_Padding61[3];       // 61..63 - probable tail padding; ctor/loader leave untouched
};

struct VertexCompat
{
    LTVector m_vVec;
};

struct SPolyVertexCompat
{
    VertexCompat *m_pPoints; // 0
    float m_fScaledU;        // 4
    float m_fScaledV;        // 8
    float m_fLightmapU;      // 12
    float m_fLightmapV;      // 16
    // Talon/D3D stores SPolyVertex diffuse bytes in D3DCOLOR memory order:
    // B, G, R, A.  d3d.ren 0x10030589/90/97 reads +0x16 as R,
    // +0x15 as G and +0x14 as B before packing the D3D diffuse color.
    uint8 m_nColorB; // 20 (0x14)
    uint8 m_nColorG; // 21 (0x15)
    uint8 m_nColorR; // 22 (0x16)
    uint8 m_nColorA; // 23 (0x17)
};

struct PolyAnimRefCompat
{
    uint16 m_wRefs[2];
};
static_assert(sizeof(PolyAnimRefCompat) == 4, "PolyAnimRefCompat size mismatch");

// Retail Talon trace and unresolved fields: docs/world_poly_layout_trace.md.
struct WorldPolyCompat
{
    uint32 m_adwData_0[3];                 // 0 - unresolved opaque storage
    PolyAnimRefCompat *m_pPolyAnimRefs;    // 12
    uint32 m_dwPolyAnimRefs;               // 16
    uint16 m_wLMPlaneAndFlags;             // 20 - basis selector bits 11..13; 0x4000 vertex-lighting dirty
    uint16 m_wIndex;                       // 22
    LTVector m_vCenter;                    // 24
    float m_fRadius;                       // 36
    void *m_pPlane;                        // 40
    SurfaceCompat *m_pSurface;             // 44
    uint32 m_adwData_48[2];                // 48 - unresolved opaque storage
    LTVector m_vLMCenter;                  // 56
    uint16 m_wPrevSurfacePoly;                    // 68 - previous polygon on the same Surface; 0xFFFF ends chain
    uint16 m_wFrameCode;                   // 70
    void *m_pLMData;                       // 72
    uint8 m_nLightmapWidth;                // 76
    uint8 m_nLightmapHeight;               // 77
    uint8 m_nLMPageX;                      // 78
    uint8 m_nLMPageY;                      // 79
    SPolyVertexCompat *m_pTJunctionVertices; // 80 - FixTJunc span; aliases m_Vertices when no extra span
    uint16 m_wNumVerts;                    // 84
    uint16 m_wNumTJunctionVerts;                 // 86 - count for m_pTJunctionVertices, including alias fallback

    // Variable-size allocation: normal vertices begin at byte 88, followed
    // by an optional T-junction-fixed span. Stock d3d.ren selects the span
    // at +80 (count +86) when FixTJunc is enabled, otherwise this inline span.
    SPolyVertexCompat m_Vertices[1]; // 88
};

struct NodeCompat;

struct CheapLTLinkCompat
{
    void *m_pData;
    void *m_pNext;
};

struct LeafListCompat
{
    uint16 m_wPortalID; // 0
    uint16 m_wSize;     // 2
    uint8 *m_pVisData;  // 4
};

struct LeafCompat
{
    uint32 m_adwData_0[4];       // 0
    LeafListCompat *m_pLists;    // 16
    void *m_Link[3];             // 20 - LTLink, 12 bytes
    WorldPolyCompat **m_pPolies; // 32
    uint32 m_dwPolies;           // 36
    float m_fData_40;            // 40
    uint16 m_wFrameCode;         // 44
    uint16 m_nLists;             // 46
};

struct NodeCompat
{
    WorldPolyCompat *m_pPoly; // 0
    NodeCompat *m_pSides[2];  // 4
    CheapLTLinkCompat m_Link; // 12
    uint16 m_wLeaf;           // 20
    uint8 m_nFlags;           // 22
    uint8 m_nPlaneType;       // 23
};

struct WorldBspCompat
{
    uint32 *m_pVTable;            // 0
    char m_szWorldName[65];       // 4
    uint8 m_nWorldNamePadding0;   // 69
    uint16 m_wWorldNamePadding1;  // 70
    uint32 m_dwWorldInfoFlags;    // 72
    uint32 m_dwData_76;           // 76
    uint32 m_dwMemoryUse;         // 80
    uint8 m_pad84_103[20];        // PolyAnimRef array
    LTPlaneCompat *m_pPlanes;     // 104
    uint32 m_dwPlanes;            // 108
    NodeCompat *m_pNodes;         // 112
    uint32 m_dwNodes;             // 116
    SurfaceCompat *m_pSurfaces;   // 120
    uint32 m_dwSurfaces;          // 124
    LeafListCompat *m_pLeafLists; // 128
    uint32 m_dwLeafLists;         // 132
    LeafCompat *m_pLeafs;         // 136
    uint32 m_dwLeafs;             // 140
    void *m_pUnkStructs144;       // 144
    uint32 m_dwUnkStructs144;     // 148
    uint32 m_dwTotalVisListSize;  // 152
    NodeCompat *m_pRootNode;      // 156
    WorldPolyCompat **m_pPolies;  // 160
    uint32 m_dwPolies;            // 164
    VertexCompat *m_pPoints;      // 168
    uint32 m_dwPoints;            // 172
    void *m_pUserPortals;         // 176
    uint32 m_dwUserPortals;       // 180
    char *m_szTextureNameData;    // 184
    char **m_szTextureNames;      // 188
    uint32 m_dwTextures;          // 192
    LTVector m_vMinBox;           // 196
    LTVector m_vMaxBox;           // 208
    uint32 m_dwData_220;          // 220
    uint32 m_adwData_224[2];      // 224
    LTVector m_vWorldTranslation; // 232
    uint32 m_dwData_244;          // 244
    uint16 m_wIndex;              // 248
    uint16 m_wData_250;           // 250
    uint8 *m_pPolyData;           // 252
    uint32 m_dwPolyDataSize;      // 256
    uint8 *m_pVisListData;        // 260
};

static_assert(sizeof(LeafListCompat) == 8, "LeafListCompat size mismatch");
static_assert(sizeof(NodeCompat) == 24, "NodeCompat size mismatch");
static_assert(sizeof(LeafCompat) == 48, "LeafCompat size mismatch");
static_assert(offsetof(WorldBspCompat, m_pNodes) == 112, "WorldBsp nodes offset mismatch");
static_assert(offsetof(WorldBspCompat, m_pLeafs) == 136, "WorldBsp leafs offset mismatch");
static_assert(offsetof(WorldBspCompat, m_pRootNode) == 156, "WorldBsp root offset mismatch");
static_assert(offsetof(WorldBspCompat, m_pVisListData) == 260, "WorldBsp vis data offset mismatch");

struct WorldDataCompat
{
    uint32 m_dwFlags;
    WorldBspCompat *m_pOriginalBsp;
    WorldBspCompat *m_pWorldBsp;
    WorldBspCompat *m_pValidBsp;
};

struct LMPolyRefCompat
{
    uint16 m_wModel;
    uint16 m_wPoly;
};

struct LMFramePolyDataCompat
{
    uint8 *m_pData;    // 0
    uint16 m_wSize;    // 4
    uint16 m_wData_6;  // 6
    uint8 *m_pReds;    // 8
    uint8 *m_pGreens;  // 12
    uint8 *m_pBlues;   // 16
    uint8 m_nVertices; // 20
    uint8 m_nData_21;
    uint16 m_wData_22;
};

struct LMFrameCompat
{
    LMFramePolyDataCompat *m_pPolyDataList;
};

struct LMAnimCompat
{
    char m_szName[32];        // 0
    int32 m_bShadowMap;       // 32
    LMFrameCompat *m_pFrames; // 36
    uint8 m_nFrames;          // 40
    uint8 m_nData_41;
    uint16 m_wData_42;
    LMPolyRefCompat *m_pPolyRefs; // 44
    uint16 m_wPolyRefs;           // 48
    uint16 m_wData_50;
    uint32 m_dwBetweenFrames[2]; // 52
    float m_fPercentBetween;     // 60
    float m_fBlendPercent;       // 64
    LTVector m_vLightPos;        // 68
    LTVector m_vLightColor;      // 80
    float m_fLightRadius;        // 92
};

static_assert(sizeof(LMFramePolyDataCompat) == 24, "LMFramePolyDataCompat size mismatch");
static_assert(sizeof(LMAnimCompat) == 96, "LMAnimCompat size mismatch");

struct LTRGBCompat
{
    uint8 b;
    uint8 g;
    uint8 r;
    uint8 a;
};

struct LightTableCompat
{
    LTRGBCompat *m_pLookup;          // 0
    uint32 m_dwFullLookupSize;       // 4
    uint32 m_adwLookupSize[3];       // 8: X,Y,Z
    int32 m_anLookupSizeMinusOne[3]; // 20
    uint32 m_dwXSizeTimesYSize;      // 32
    LTVector m_vBlockSize;           // 36
    LTVector m_vReciBlockSize;       // 48
    LTVector m_vLookupStart;         // 60
};

static_assert(sizeof(LTRGBCompat) == 4, "LTRGBCompat size mismatch");
static_assert(sizeof(LightTableCompat) == 72, "LightTableCompat size mismatch");

struct MainWorldCompat
{
    uint32 *m_pVTable;                                                       // 0
    CMoArrayDefaultCacheCompat<LMAnimCompat> m_LMAnims;                      // 4
    CMoArrayDefaultCacheCompat<LMPolyRefCompat> m_LMPolyRefs;                // 24
    CMoArrayDefaultCacheCompat<LMFrameCompat> m_LMFrames;                    // 44
    CMoArrayDefaultCacheCompat<uint8> m_LMData;                              // 64
    CMoArrayDefaultCacheCompat<LMFramePolyDataCompat> m_LMFramePolyDataList; // 84
    uint32 m_dwRenderDataPos;                                                // 104
    uint8 m_pad108_243[136];                                                 // 108
    SurfaceEffectCompat *m_pSurfaceEffects;                                  // 244
    float m_fLMGridSize;                                                     // 248
    LightTableCompat m_LightTable;                                           // 252
    LTVector m_vExtentsMin;                                                  // 324
    LTVector m_vExtentsMax;                                                  // 336
    LTVector m_vExtentsDiffScale;                                            // 348
    LTVector m_vExtentsMinExtra;                                             // 360
    LTVector m_vExtentsMaxExtra;                                             // 372
    uint32 m_dwFlags;                                                        // 384
    void *m_pFileStream;                                                     // 388
    CMoArrayDefaultCacheCompat<WorldDataCompat *> m_WorldModels;             // 392
    CMoArrayDefaultCacheCompat<WorldPolyCompat *> m_Polies;                  // 412
};

static_assert(offsetof(MainWorldCompat, m_fLMGridSize) == 248, "MainWorld LM grid offset mismatch");
static_assert(offsetof(MainWorldCompat, m_LightTable) == 252, "MainWorld LightTable offset mismatch");
static_assert(offsetof(MainWorldCompat, m_Polies) == 412, "MainWorld polies offset mismatch");

constexpr uint32 WIF_MAINWORLD = (1u << 2);
constexpr uint32 WIF_TERRAIN = (1u << 3);
constexpr uint32 WIF_PHYSICSBSP = (1u << 4);
constexpr uint32 WIF_VISBSP = (1u << 5);

constexpr uint32 SURF_SOLID = (1u << 0);
constexpr uint32 SURF_NONEXISTANT = (1u << 1);
constexpr uint32 SURF_INVISIBLE = (1u << 2);
constexpr uint32 SURF_TRANSPARENT = (1u << 3);
constexpr uint32 SURF_SKY = (1u << 4);
constexpr uint32 SURF_BRIGHT = (1u << 5);
constexpr uint32 SURF_FLATSHADE = (1u << 6);
constexpr uint32 SURF_LIGHTMAP = (1u << 7);
constexpr uint32 SURF_DIRECTIONALLIGHT = (1u << 11);
constexpr uint32 SURF_GOURAUDSHADE = (1u << 12);
constexpr uint32 SURF_PORTAL = (1u << 13);
constexpr uint32 SURF_SPRITEANIMATE = (1u << 14);
constexpr uint32 SURF_PANNINGSKY = (1u << 15);
constexpr uint32 SURF_ADDITIVE = (1u << 19);

static_assert(sizeof(SurfaceCompat) == 64, "SurfaceCompat size mismatch");
static_assert(offsetof(SurfaceCompat, m_Nexus) == 36, "Surface Nexus offset mismatch");
static_assert(offsetof(SurfaceCompat, m_pTexture) == 44, "Surface texture offset mismatch");
static_assert(offsetof(SurfaceCompat, m_dwFlags) == 48, "Surface flags offset mismatch");
static_assert(offsetof(SurfaceCompat, m_wTextureFlags) == 52, "Surface texture flags offset mismatch");
static_assert(offsetof(SurfaceCompat, m_wTexture) == 54, "Surface texture index offset mismatch");
static_assert(offsetof(SurfaceCompat, m_wPoly) == 56, "Surface poly offset mismatch");
static_assert(offsetof(SurfaceCompat, m_wPortalIDAndFlags) == 58, "Surface portal offset mismatch");
static_assert(offsetof(SurfaceCompat, m_nData_60) == 60, "Surface serialized byte offset mismatch");
static_assert(offsetof(SurfaceCompat, m_Padding61) == 61, "Surface tail padding offset mismatch");
static_assert(sizeof(SPolyVertexCompat) == 24, "SPolyVertexCompat size mismatch");
static_assert(offsetof(WorldPolyCompat, m_wLMPlaneAndFlags) == 20, "WorldPoly plane basis/flags offset mismatch");
static_assert(offsetof(WorldPolyCompat, m_wPrevSurfacePoly) == 68, "WorldPoly surface chain offset mismatch");
static_assert(offsetof(WorldPolyCompat, m_pTJunctionVertices) == 80, "WorldPoly vertex pointer offset mismatch");
static_assert(offsetof(WorldPolyCompat, m_wNumVerts) == 84, "WorldPoly vertex count offset mismatch");
static_assert(offsetof(WorldPolyCompat, m_wNumTJunctionVerts) == 86, "WorldPoly T-junction vertex count offset mismatch");
static_assert(offsetof(WorldPolyCompat, m_Vertices) == 88, "WorldPoly inline vertex offset mismatch");
static_assert(offsetof(MainWorldCompat, m_WorldModels) == 392, "MainWorld worldmodels offset mismatch");

struct RMode
{
    LTBOOL m_bHardware;
    char m_szRenderDLL[256];
    char m_szInternalName[128];
    char m_szDescription[128];
    uint32 m_dwWidth;
    uint32 m_dwHeight;
    uint32 m_dwBitDepth;
    RMode *m_pNext;
};

struct RenderStructInit
{
    int m_nRendererVersion;
    RMode m_Mode;
    HWND m_hWnd;
};

constexpr uint32 FLAG_VISIBLE = (1u << 0);
constexpr uint32 FLAG_SPRITEBIAS = (1u << 2);
constexpr uint32 FLAG_ROTATEABLESPRITE = (1u << 3);
constexpr uint32 FLAG_SPRITE_NOZ = (1u << 4);
// Type-specific alias used by particle systems and PolyGrids.  Talon's
// client-side FX update code skips expensive animation when this bit was not
// set by the renderer on the previous frame.
constexpr uint32 FLAG_WASDRAWN = (1u << 4);
// Renderer visibility handshake. Retail d3d.ren sets this bit in LTObject::m_Flags
// after a ParticleSystem/PolyGrid is actually submitted. CClientMgr consumes it
// on the next client update and translates it into FLAG_WASDRAWN for ClientShell FX.
constexpr uint32 FLAG_INTERNAL1 = (1u << 30);
constexpr uint32 FLAG_GLOWSPRITE = (1u << 5);
constexpr uint32 FLAG_ENVIRONMENTMAP = (1u << 5);
// OT_LIGHT / general lighting flags.  These bit positions are shared with
// type-specific flags (for example GLOWSPRITE), exactly as in Talon.
constexpr uint32 FLAG_ONLYLIGHTWORLD = (1u << 5);
constexpr uint32 FLAG_REALLYCLOSE = (1u << 6);
constexpr uint32 FLAG_DONTLIGHTBACKFACING = (1u << 6);
constexpr uint32 FLAG_FOGDISABLE = (1u << 7);
constexpr uint32 FLAG_ONLYLIGHTOBJECTS = (1u << 7);
constexpr uint32 FLAG_NOLIGHT = (1u << 9);

constexpr uint32 FLAG2_FORCEDYNAMICLIGHTWORLD = (1u << 0);
constexpr uint32 FLAG2_CHROMAKEY = (1u << 1);
constexpr uint32 FLAG2_ADDITIVE = (1u << 2);
constexpr uint32 FLAG2_MULTIPLY = (1u << 3);
// WorldModel object-level binding that authorizes SURF_TRANSPARENT polygons
// to participate in Talon's translucent WorldModel pass.  A brush surface
// carrying SURF_TRANSPARENT by itself remains opaque.
constexpr uint32 FLAG2_FORCETRANSLUCENT = (1u << 6);
constexpr uint32 FLAG2_SPRITE_TROTATE = (1u << 9);

constexpr uint8 OT_NORMAL = 0;
constexpr uint8 OT_MODEL = 1;
constexpr uint8 OT_WORLDMODEL = 2;
constexpr uint8 OT_SPRITE = 3;
constexpr uint8 OT_LIGHT = 4;
constexpr uint8 OT_CAMERA = 5;
constexpr uint8 OT_PARTICLESYSTEM = 6;
constexpr uint8 OT_POLYGRID = 7;
constexpr uint8 OT_LINESYSTEM = 8;
constexpr uint8 OT_CONTAINER = 9;
constexpr uint8 OT_CANVAS = 10;

constexpr int DRAWMODE_NORMAL = 1;
constexpr int DRAWMODE_OBJECTLIST = 2;

constexpr uint32 MAX_MODEL_TEXTURES = 4;
constexpr uint32 MAX_PIECES_PER_MODEL = 32;

struct SkyDef
{
    LTVector m_vMin;
    LTVector m_vMax;
    LTVector m_vViewMin;
    LTVector m_vViewMax;
};

struct ModelHookData
{
    LTObject *m_pObject;
    uint32 m_dwHookFlags;
    uint32 m_dwObjectFlags;
    LTVector *m_pLightAdd;
    LTVector *m_pObjectColor;
};

struct SceneDesc
{
    int m_nDrawMode;

    uint32 *m_pObjectTicks;
    uint32 *m_pModelTicks;
    uint32 *m_pSpriteTicks;
    uint32 *m_pWorldModelTicks;
    uint32 *m_pParticleSystemTicks;
    uint32 *m_pLightProcessTicks;

    LTVector m_vModelLightAdd;
    LTVector m_vModelLightAddDir;

    RenderContext *m_pRenderContext;

    LTVector m_vGlobalLightColor;
    LTVector m_vGlobalLightDir;

    LTVector m_vGlobalLightScale;
    LTVector m_vGlobalVertexTint;
    LTVector m_vGlobalWMAmbient;
    LTVector m_vGlobalLightAdd;

    float m_fFrameTime;

    SkyDef m_SkyDef;
    LTObject **m_pSkyObjects;
    int m_nSkyObjects;

    LTRect m_rcViewport;

    float m_fFovX;
    float m_fFovY;
    float m_fFarZ;

    LTVector m_vPos;
    LTRotation m_rRotation;

    LTObject **m_pObjectList;
    int m_nObjectListSize;

    void (*m_ModelHookFn)(ModelHookData *, void *);
    void *m_pModelHookUser;
};

// d3d.ren RenderScene (0x10014CC4) passes SceneDesc+0x50 to its
// final full-screen light-scale / InvertHack pass (0x10015240).
static_assert(offsetof(SceneDesc, m_vGlobalLightScale) == 0x50,
              "SceneDesc global-light-scale offset mismatch");

struct LTMatrix
{
    float m[4][4];
};

template <typename T>
struct CMoArrayNoCache
{
    uint32 *m_pVTable;
    T *m_pArray;
    uint32 m_dwElements;
    uint32 m_dwPadding;
};

struct NewVertexWeight
{
    float m_afVec[4];
    uint32 m_dwNode;
};

struct UVPair
{
    float m_fU;
    float m_fV;
};

struct ModelTri
{
    uint16 m_awIndices[3];
    UVPair m_UVs[3];
};

struct ModelVert
{
    NewVertexWeight *m_pWeights;
    uint16 m_wWeights;
    uint16 m_wReplacement;
    LTVector m_vVec;
    LTVector m_vNormal;
};

struct Model;

struct PieceLOD
{
    CMoArrayNoCache<ModelVert> m_Verts; // 0
    CMoArrayNoCache<ModelTri> m_Tris;   // 16
    Model *m_pModel;                    // 32
};

struct LODInfoCompat
{
    float m_fDist;
};

struct ModelPiece
{
    CMoArrayNoCache<ModelVert> m_Verts; // 0
    CMoArrayNoCache<ModelTri> m_Tris;   // 16

    uint32 m_dwData0;       // 32
    uint16 m_wTextureIndex; // 36
    uint16 m_wData38;
    uint32 m_dwData40;
    float m_fSpecularPower;
    float m_fSpecularScale;

    CMoArrayNoCache<PieceLOD> m_LODs; // 52
    float m_fLODWeight;               // 68
    char m_szName[32];                // 72
    void *m_pModel;                   // 104
};

struct ModelNodeCompat
{
    uint32 *m_pVTable;                             // 0
    LTVector m_vOffsetFromParent;                  // 4
    uint16 m_wNodeIndex;                           // 16
    uint8 m_nFlags;                                // 18
    uint8 m_nData19;                               // 19
    uint32 m_dwScratch;                            // 20
    CMoArrayNoCache<ModelNodeCompat *> m_Children; // 24
    uint8 m_pad40_175[136];
    const char *m_szName; // 176
};
static_assert(offsetof(ModelNodeCompat, m_Children) == 24, "ModelNode children offset mismatch");

struct Model
{
    uint32 *m_pVTable;    // 0
    char *m_szFilename;   // 4
    uint8 m_pad08_35[28]; // 8..35

    CMoArrayNoCache<void *> m_Nodes;        // 36
    CMoArrayNoCache<ModelPiece *> m_Pieces; // 52

    uint8 m_pad68_99[32];
    uint32 m_nTotalVerts;                      // 100
    uint32 m_nTotalTris;                       // 104
    uint8 m_pad108_139[32];                    // 108..139
    CMoArrayNoCache<LODInfoCompat> m_LODInfos; // 140..155
    uint32 m_dwData156;                        // 156
    uint32 m_dwData160;                        // 160
    float m_fGlobalRadius;                     // 164
    float m_fVisRadius;                        // 168
    uint8 m_pad172_315[144];                   // 172..315
    int32 m_bNormalRef;                        // 316
    int32 m_bFOVOffset;                        // 320
    float m_fFOVOffsetX;                       // 324
    float m_fFOVOffsetY;                       // 328
    int32 m_bSpecularEnable;                   // 332
    int32 m_bRigid;                            // 336
    uint8 m_pad340_707[368];                   // 340..707
    ModelNodeCompat *m_pRootNode;              // 708
};
static_assert(offsetof(Model, m_LODInfos) == 140, "Model LOD info offset mismatch");
static_assert(offsetof(Model, m_dwData156) == 156, "Model +156 offset mismatch");
static_assert(offsetof(Model, m_dwData160) == 160, "Model +160 offset mismatch");
static_assert(offsetof(Model, m_fGlobalRadius) == 164, "Model global radius offset mismatch");
static_assert(offsetof(Model, m_fVisRadius) == 168, "Model vis radius offset mismatch");
static_assert(offsetof(Model, m_bRigid) == 336, "Model rigid offset mismatch");
static_assert(offsetof(Model, m_pRootNode) == 708, "Model root node offset mismatch");

struct LTLinkCompat
{
    void *m_pPrev;
    void *m_pNext;
    void *m_pData;
};

#pragma pack(push, 1)
struct DtxExtraCompat
{
    uint8 m_nTexGroup;
    uint8 m_nMipMapsInUse;
    uint8 m_nBPPIdent;
    uint8 m_nMipMapOffsetNC;
    uint8 m_nMipMapOffsetED;
    uint8 m_nTexPriority;
    float m_fDetTexScale;
    int16 m_nDetTexAngle;
};
#pragma pack(pop)

struct DtxHeaderCompat
{
    uint32 m_dwResType;
    int32 m_nVersion;
    uint16 m_wBaseWidth;
    uint16 m_wBaseHeight;
    uint16 m_wMipmaps;
    uint16 m_wSections;
    int32 m_nIFlags;
    int32 m_nUserFlags;
    DtxExtraCompat m_Extra;
    char m_szCommandString[128];

    uint32 GetBPPIdent() const
    {
        return m_Extra.m_nBPPIdent == 0 ? static_cast<uint32>(BPP_32) : static_cast<uint32>(m_Extra.m_nBPPIdent);
    }
};

struct TextureMipDataCompat
{
    uint32 m_dwWidth;
    uint32 m_dwHeight;
    uint8 *m_pData;
    int32 m_nPitch;
    uint32 m_dwData16;
    uint32 m_dwData20;
};

template <typename T>
struct StdVectorCompat
{
    T *m_pFirst;
    T *m_pLast;
    T *m_pEnd;

    uint32 size() const
    {
        if (!m_pFirst || !m_pLast || m_pLast < m_pFirst)
            return 0;
        return static_cast<uint32>(m_pLast - m_pFirst);
    }
};

struct RenderStateCompat
{
    uint32 m_dwRenderStateType;
    uint32 m_dwRenderState;
};

struct TextureStateCompat
{
    uint32 m_dwStage;
    uint32 m_dwTextureStateType;
    uint32 m_dwTextureState;
};

struct StateChangeCompat
{
    StdVectorCompat<RenderStateCompat> m_RenderList;
    StdVectorCompat<TextureStateCompat> m_TextureList;
};

static_assert(sizeof(StdVectorCompat<uint32>) == 12, "StdVectorCompat x86 layout mismatch");
static_assert(sizeof(RenderStateCompat) == 8, "RenderStateCompat layout mismatch");
static_assert(sizeof(TextureStateCompat) == 12, "TextureStateCompat layout mismatch");
static_assert(sizeof(StateChangeCompat) == 24, "StateChangeCompat layout mismatch");

struct SharedTextureCompat
{
    NexusCompat m_Nexus;                   // 0
    void *m_pEngineData;                   // 8
    void *m_pRenderData;                   // 12
    LTLinkCompat m_Link;                   // 16
    uint32 m_adwData28[2];                 // 28
    void *m_pFile;                         // 36
    SharedTextureCompat *m_pLinkedTexture; // 40
    uint32 m_eTexType;                     // 44
    uint16 m_wFrameCode;                   // 48
    uint16 m_wFlags;                       // 50
    void *m_pStateChange;                  // 52
    char *m_szCommandString;               // 56
    uint32 m_dwMipMapOffsetED;             // 60
};

struct TextureDataCompat
{
    uint32 m_dwVTable;                     // 0
    uint32 m_dwResType;                    // 4
    DtxHeaderCompat m_DtxHeader;           // 8
    LTLinkCompat m_Link;                   // 172
    uint32 m_dwAllocSize;                  // 184
    void *m_pDtxSections;                  // 188
    SharedTextureCompat *m_pSharedTexture; // 192
    uint32 m_dwFlags;                      // 196
    uint8 *m_pDataBuffer;                  // 200
    TextureMipDataCompat m_Mips[8];        // 204
};

static_assert(sizeof(DtxExtraCompat) == 12, "DtxExtra layout mismatch");
static_assert(sizeof(DtxHeaderCompat) == 164, "DtxHeader layout mismatch");
static_assert(offsetof(SharedTextureCompat, m_pRenderData) == 12, "SharedTexture render-data offset mismatch");
static_assert(offsetof(SharedTextureCompat, m_pFile) == 36, "SharedTexture file offset mismatch");
static_assert(offsetof(SharedTextureCompat, m_pLinkedTexture) == 40, "SharedTexture linked-texture offset mismatch");
static_assert(offsetof(SharedTextureCompat, m_eTexType) == 44, "SharedTexture texture-type offset mismatch");
static_assert(offsetof(SharedTextureCompat, m_dwMipMapOffsetED) == 60, "SharedTexture mip offset mismatch");
static_assert(sizeof(SharedTextureCompat) == 64, "SharedTexture size mismatch");
static_assert(offsetof(TextureDataCompat, m_DtxHeader) == 8, "TextureData DTX offset mismatch");
static_assert(offsetof(TextureDataCompat, m_Mips) == 204, "TextureData mip offset mismatch");

struct ModelInstanceVTable
{
    void *m_entries0_16[17];
    float(__fastcall *GetRadius)(void *);
    LTMatrix *(__fastcall *GetNodeTransforms)(void *);
    LTMatrix *(__fastcall *GetNodeTransform)(void *, void *, uint32);
    BOOL(__fastcall *HasValidNodeTransforms)(void *);
};

// Renderer-only view onto the engine's LTObject/ModelInstance memory.
// Offsets are from the reconstructed AVP2 Talon structures.
struct LTObjectCompat
{
    uint32 *m_pVTable;      // 0, inherited WorldTreeObj vtable
    uint8 m_pad04_87[84];   // WorldTreeObj links/type
    uint32 m_dwWTFrameCode; // 88
    uint8 m_pad92_135[44];
    uint32 m_dwFlags;     // 136
    uint32 m_dwFlags2;    // 140
    uint32 m_dwUserFlags; // 144
    uint8 m_nColorR;      // 148
    uint8 m_nColorG;
    uint8 m_nColorB;
    uint8 m_nColorA;
    Attachment *m_pAttachments; // 152
    LTRotation m_rRot;          // 156
    LTVector m_vScale;          // 172
    uint16 m_wObjectID;         // 184
    uint16 m_wSerializeID;
    uint8 m_nObjectType; // 188
    uint8 m_nBPriority;
    uint16 m_wData2;
    void *m_pUserData; // 192
    uint8 m_pad196_291[96];
    uint32 m_dwInternalFlags; // 292
    uint8 m_pad296_391[96];
    // d3d.ren 0x10022B99 tests byte +0x188 bit 0x10 when splitting
    // OT_CANVAS between the solid-canvas pass and the sorted translucent
    // canvas queue.  This is the client-side flags dword.
    uint32 m_dwClientFlags; // 392 (0x188)
    uint8 m_pad396_399[4];
    void *m_pSrvObjData; // 400
    LTVector m_vPos;     // 404
    LTVector m_vDims;    // 416
    float m_fRadius;     // 428
};

struct DynamicLightCompat
{
    LTObjectCompat m_Base; // 0..431
    float m_fLightRadius;  // 432
};
static_assert(offsetof(DynamicLightCompat, m_fLightRadius) == 432, "Dynamic light radius offset mismatch");

struct StaticLightCompat
{
    uint8 m_worldTreeObj[92]; // 0..91
    uint8 m_link[12];         // 92..103
    LTVector m_vPos;          // 104
    float m_fRadius;          // 116
    LTVector m_vInnerColor;   // 120
    LTVector m_vDir;          // 132
    float m_fFOV;             // 144
    LTVector m_vOuterColor;   // 148
};
static_assert(offsetof(StaticLightCompat, m_vPos) == 104, "Static light pos offset mismatch");
static_assert(offsetof(StaticLightCompat, m_fRadius) == 116, "Static light radius offset mismatch");

struct WorldModelInstanceCompat
{
    LTObjectCompat m_Base;
    WorldBspCompat *m_pOriginalBsp; // 432
    WorldBspCompat *m_pWorldBsp;    // 436
    WorldBspCompat *m_pValidBsp;    // 440
    uint8 m_pad444_503[60];
    LTMatrix m_mTransform;     // 504
    LTMatrix m_mBackTransform; // 568
};
static_assert(offsetof(WorldModelInstanceCompat, m_pOriginalBsp) == 432, "WorldModel original BSP offset mismatch");
static_assert(offsetof(WorldModelInstanceCompat, m_pWorldBsp) == 436, "WorldModel world BSP offset mismatch");
static_assert(offsetof(WorldModelInstanceCompat, m_pValidBsp) == 440, "WorldModel valid BSP offset mismatch");
static_assert(offsetof(WorldModelInstanceCompat, m_mTransform) == 504, "WorldModel transform offset mismatch");

struct ModelInstanceCompat
{
    LTObjectCompat m_Base;                        // 0..431
    uint32 m_dwData432;                           // 432
    void *m_pFileIdentifier;                      // 436
    uint32 m_dwData440;                           // 440
    void *m_pInstanceHookFn;                      // 444
    void *m_pSkins[MAX_MODEL_TEXTURES];           // 448
    uint8 m_animTracker[80];                      // 464
    void *m_pAnimTrackers;                        // 544
    CMoArrayNoCache<uint8> m_CachedLocators;      // 548 (opaque)
    CMoArrayNoCache<LTMatrix> m_CachedTransforms; // 564
    void *m_pNCFunc;                              // 580
    void *m_pNCUserData;                          // 584
    uint32 m_adwHiddenPiece[1];                   // 588, MAX_PIECES_PER_MODEL/32
};

static_assert(sizeof(LTRotation) == 16, "LTRotation must be four floats");
static_assert(offsetof(LTObjectCompat, m_rRot) == 156, "LTObject rotation offset mismatch");
static_assert(offsetof(LTObjectCompat, m_vScale) == 172, "LTObject scale offset mismatch");
static_assert(offsetof(LTObjectCompat, m_dwWTFrameCode) == 88, "LTObject WT frame offset mismatch");
static_assert(offsetof(LTObjectCompat, m_dwFlags) == 136, "LTObject flags offset mismatch");
static_assert(offsetof(LTObjectCompat, m_dwInternalFlags) == 292, "LTObject internal flags offset mismatch");
static_assert(offsetof(LTObjectCompat, m_dwClientFlags) == 0x188, "LTObject client-flags offset mismatch");
static_assert(offsetof(LTObjectCompat, m_pSrvObjData) == 400, "LTObject srv data offset mismatch");
static_assert(offsetof(LTObjectCompat, m_nObjectType) == 188, "LTObject type offset mismatch");
static_assert(offsetof(LTObjectCompat, m_vPos) == 404, "LTObject position offset mismatch");
static_assert(sizeof(LTObjectCompat) == 432, "LTObjectCompat size mismatch");
static_assert(offsetof(ModelInstanceCompat, m_pSkins) == 448, "ModelInstance skins offset mismatch");
static_assert(offsetof(ModelInstanceCompat, m_CachedTransforms) == 564, "ModelInstance transform array offset mismatch");
static_assert(offsetof(ModelInstanceCompat, m_adwHiddenPiece) == 588, "ModelInstance hidden-piece offset mismatch");

struct SpriteEntryCompat
{
    SharedTexture *m_pTexture;
};

struct SpriteAnimCompat
{
    char m_szName[32];
    SpriteEntryCompat *m_pFrames;
    uint32 m_nFrames;
    uint32 m_dwAnimLengthMS;
    uint32 m_dwFrameRateMS;
    LTBOOL m_bKeyed;
    uint32 m_dwColourKey;
    LTBOOL m_bTranslucent;
};

struct FileIdentifierCompat
{
    void *m_pData;
    LTLinkCompat m_Link;
    void *m_pFileTree;
    uint16 m_nFileID;
    uint16 m_nNameLen;
    uint8 m_nTypeCode;
    uint8 m_nFlags;
    uint16 m_nPad;
    char *m_pFilename;
};

struct SpriteCompat
{
    LTLinkCompat m_Link;        // 0x00..0x0B
    SpriteAnimCompat *m_pAnims; // 0x0C
    uint32 m_nAnims;            // 0x10

    // AVP2 retail Sprite objects do NOT store a FileIdentifier* at +0x14.
    // A VS2022 crash dump from a live PolyGrid shows this tail contains the
    // inline 8-byte tag/name "Unknown\0".  Keep it opaque/inline so renderer
    // code cannot accidentally reinterpret those characters as a pointer.
    char m_szTag[8]; // 0x14..0x1B
};

static_assert(offsetof(SpriteCompat, m_pAnims) == 0x0C, "Sprite anim pointer offset mismatch");
static_assert(offsetof(SpriteCompat, m_nAnims) == 0x10, "Sprite anim count offset mismatch");
static_assert(offsetof(SpriteCompat, m_szTag) == 0x14, "Sprite inline tag offset mismatch");
static_assert(sizeof(SpriteCompat) == 0x1C, "SpriteCompat size mismatch");

struct SpriteTrackerCompat
{
    SpriteCompat *m_pSprite;
    SpriteAnimCompat *m_pCurAnim;
    SpriteEntryCompat *m_pCurFrame;
    uint32 m_dwCurTimeMS;
    uint32 m_dwFlags;
};

struct SpriteControlImplCompat
{
    uint32 *m_pVTable;
    void *m_pSprite;
};

struct SpriteInstanceCompat
{
    LTObjectCompat m_Base;               // 0..431
    SpriteTrackerCompat m_SpriteTracker; // 432..451
    uint32 m_hClipperPoly;               // 452
    SpriteControlImplCompat m_SCImpl;    // 456..463
};

static_assert(sizeof(SpriteTrackerCompat) == 20, "SpriteTrackerCompat size mismatch");
static_assert(sizeof(SpriteControlImplCompat) == 8, "SpriteControlImplCompat size mismatch");
static_assert(offsetof(SpriteInstanceCompat, m_Base) == 0, "Sprite base offset mismatch");
static_assert(offsetof(SpriteInstanceCompat, m_SpriteTracker) == 432, "Sprite tracker offset mismatch");
static_assert(offsetof(SpriteInstanceCompat, m_SpriteTracker.m_pCurFrame) == 440, "Sprite current frame offset mismatch");
static_assert(offsetof(SpriteInstanceCompat, m_hClipperPoly) == 452, "Sprite clipper offset mismatch");
static_assert(offsetof(SpriteInstanceCompat, m_SCImpl) == 456, "Sprite control offset mismatch");
static_assert(sizeof(SpriteInstanceCompat) == 464, "SpriteInstanceCompat size mismatch");

struct LTParticleCompat
{
    LTVector m_vVel;           // 0
    LTVector m_vColor;         // 12
    float m_fAlpha;            // 24
    float m_fSize;             // 28
    LTParticleCompat *m_pNext; // 32
    LTVector m_vPos;           // 36
    float m_fLifetime;         // 48
    float m_fTotalLifetime;    // 52
    LTParticleCompat *m_pPrev; // 56
};

struct ParticleSystemCompat
{
    LTObjectCompat m_Base;           // 0..431
    LTParticleCompat m_ParticleHead; // 432..491
    void *m_pParticleBank;           // 492
    SharedTexture *m_pCurTexture;    // 496
    uint8 m_nSoftwareR;              // 500
    uint8 m_nSoftwareG;
    uint8 m_nSoftwareB;
    uint8 m_nPadding;
    SpriteCompat *m_pSprite;             // 504
    SpriteTrackerCompat m_SpriteTracker; // 508..527
    LTVector m_vSystemCenter;            // 528
    float m_fSystemRadius;               // 540
    LTVector m_vOldCenter;               // 544
    float m_fOldRadius;                  // 556
    int32 m_nParticles;                  // 560
    int32 m_nChangedParticles;           // 564
    LTVector m_vMinPos;                  // 568
    LTVector m_vMaxPos;                  // 580
    float m_fGravityAccel;               // 592
    float m_fParticleRadius;             // 596
    int32 m_nSrcBlend;                   // 600
    int32 m_nDestBlend;                  // 604
    uint32 m_dwSystemFlags;              // 608
};

// OT_LINESYSTEM layout reconstructed directly from the AVP2
// d3d.ren draw routine at 0x10023D80.  A line node contains two local-space
// points followed by its intrusive-list linkage.  The renderer reads the
// next pointer at node+0x40 and the LineSystem sentinel begins at object+0x1B8.
struct LSPointCompat
{
    LTVector m_vPos; // 0x00
    float m_fR;      // 0x0C
    float m_fG;      // 0x10
    float m_fB;      // 0x14
    float m_fA;      // 0x18
};

struct LSLineCompat
{
    LSPointCompat m_Points[2]; // 0x00..0x37
    uint8 m_pad38_63[8];       // 0x38..0x3F
    LSLineCompat *m_pNext;     // 0x40
    LSLineCompat *m_pPrev;     // 0x44
};

struct LineSystemCompat
{
    LTObjectCompat m_Base;   // 0x000..0x1AF
    uint8 m_pad1B0_1B7[8];   // 0x1B0..0x1B7
    LSLineCompat m_LineHead; // 0x1B8
};

// OT_CANVAS ABI reconstructed only from the AVP2 d3d.ren.
// 0x10022476 tests callback +0x1B0, then 0x10022491 pushes userdata
// +0x1B4, Canvas*, and the renderer DrawPoly manager before calling it.
struct DrawPolyMgrCompat;
struct CanvasCompat;
using CanvasDrawFnCompat = void(__cdecl *)(DrawPolyMgrCompat *, CanvasCompat *, void *);

struct CanvasCompat
{
    LTObjectCompat m_Base;    // 0x000..0x1AF
    CanvasDrawFnCompat m_pFn; // 0x1B0
    void *m_pFnUserData;      // 0x1B4
};

// d3d.ren 0x100226E9 consumes a 32-byte vertex and submits FVF 0x1C4
// (XYZRHW | DIFFUSE | SPECULAR | TEX1).  Before submission Talon may
// overwrite RHW while transforming/clipping the XYZ source coordinates.
struct CanvasPrimVertexCompat
{
    float x, y, z, rhw; // 0x00..0x0F
    uint32 diffuse;     // 0x10 D3DCOLOR ARGB
    uint32 specular;    // 0x14 D3DCOLOR ARGB
    float u, v;         // 0x18..0x1F
};

struct PGColorCompat
{
    // Retail d3d.ren indexes this table in 16-byte strides and reads four
    // floats before converting the channels to D3DCOLOR.  Values are in the
    // traditional Talon 0..255 color domain, not normalized 0..1 values.
    float r, g, b, a;
};

constexpr uint32 POLY_GRID_COLOR_TABLE_SIZE = 256;

struct PolyGridCompat
{
    LTObjectCompat m_Base;                                   // 0..431
    int8 *m_pData;                                           // 432
    uint16 *m_pIndices;                                      // 436
    SpriteCompat *m_pSprite;                                 // 440
    SpriteTrackerCompat m_SpriteTracker;                     // 444..463
    SharedTexture *m_pEnvMap;                                // 464
    float m_fPanX;                                           // 468
    float m_fPanY;                                           // 472
    float m_fScaleX;                                         // 476
    float m_fScaleY;                                         // 480
    uint32 m_dwTris;                                         // 484
    uint32 m_dwIndices;                                      // 488
    LTLinkCompat m_LeafLinks;                                // 492
    uint32 m_dwWidth;                                        // 504
    uint32 m_dwHeight;                                       // 508
    PGColorCompat m_aColorTable[POLY_GRID_COLOR_TABLE_SIZE]; // 512
};

static_assert(sizeof(LTParticleCompat) == 60, "LTParticleCompat size mismatch");
static_assert(offsetof(ParticleSystemCompat, m_pCurTexture) == 496, "Particle texture offset mismatch");
static_assert(offsetof(ParticleSystemCompat, m_nParticles) == 560, "Particle count offset mismatch");
static_assert(sizeof(LSPointCompat) == 28, "Line-system point layout mismatch");
static_assert(sizeof(LSLineCompat) == 72, "Line-system node layout mismatch");
static_assert(offsetof(LSLineCompat, m_pNext) == 0x40, "Line-system next-link offset mismatch");
static_assert(offsetof(LineSystemCompat, m_LineHead) == 0x1B8, "Line-system sentinel offset mismatch");
static_assert(offsetof(LineSystemCompat, m_LineHead) + offsetof(LSLineCompat, m_pNext) == 0x1F8,
              "Line-system first-link offset mismatch");
static_assert(offsetof(CanvasCompat, m_pFn) == 0x1B0, "Canvas callback offset mismatch");
static_assert(offsetof(CanvasCompat, m_pFnUserData) == 0x1B4, "Canvas userdata offset mismatch");
static_assert(sizeof(CanvasPrimVertexCompat) == 32, "Canvas primitive vertex layout mismatch");
static_assert(offsetof(PolyGridCompat, m_pData) == 432, "PolyGrid data offset mismatch");
static_assert(offsetof(PolyGridCompat, m_SpriteTracker) == 444, "PolyGrid tracker offset mismatch");
static_assert(offsetof(PolyGridCompat, m_dwWidth) == 504, "PolyGrid width offset mismatch");
static_assert(offsetof(PolyGridCompat, m_aColorTable) == 512, "PolyGrid color table offset mismatch");
static_assert(sizeof(PGColorCompat) == 16, "PolyGrid color entry layout mismatch");
static_assert(sizeof(PolyGridCompat) == 0x1200, "PolyGrid object layout mismatch");

inline Model *GetModelFromInstance(ModelInstanceCompat *inst)
{
    // LTAnimTracker::m_TimeRef.m_pModel is 40 bytes into the tracker.
    return *reinterpret_cast<Model **>(inst->m_animTracker + 40);
}

struct BlitRequest
{
    HLTBUFFER m_hBuffer;
    uint32 m_dwBlitOptions;
    GenericColor m_dwTransparentColor;
    LTRect *m_pSrcRect;
    LTRect *m_pDestRect;
    float m_fAlpha;
    LTWarpPt *m_pWarpPts;
    int m_nWarpPts;
};

struct GlobalPanInfo
{
    SharedTexture *m_pTexture;
    float m_fCurSkyXOffset;
    float m_fCurSkyZOffset;
    float m_fPanSkyScaleX;
    float m_fPanSkyScaleZ;
};

struct RenderStruct
{
    LTObject *(*ProcessAttachment)(LTObject *, Attachment *);

    SharedTexture *(*GetSharedTexture)(const char *);
    TextureData *(*GetTexture)(SharedTexture *);
    void (*FreeTexture)(SharedTexture *);

    void (*RunConsoleString)(char *);
    void (*ConsolePrint)(char *, ...);

    HLTPARAM (*GetParameter)(char *);
    float (*GetParameterValueFloat)(HLTPARAM);
    char *(*GetParameterValueString)(HLTPARAM);

    void (*RendererPing)();
    uint32 (*IncObjectFrameCode)();
    uint32 (*GetObjectFrameCode)();
    uint16 (*IncCurTextureFrameCode)();

    void *(*Alloc)(uint32);
    void (*Free)(void *);

    uint32 m_dwWidth;
    uint32 m_dwHeight;
    LTBOOL m_bInitted;

    uint32 m_dwTextureMem;
    uint32 m_dwLightmapsMem;
    uint32 m_dwRendererTextureMem;
    uint32 m_dwMPSavedMem;

    uint32 m_dwTicks_TVL;
    uint32 m_dwTicks_FOQ;
    uint32 m_dwTicks_Models;
    uint32 m_dwTicks_WM;
    uint32 m_dwTicks_TWM;
    uint32 m_dwTicks_Sky;

    int (*Init)(RenderStructInit *);
    void (*Term)();

    void (*BindTexture)(SharedTexture *, LTBOOL);
    void (*UnbindTexture)(SharedTexture *);

    void (*RebindLightmaps)(RenderContext *);

    RenderContext *(*CreateContext)(RenderContextInit *);
    void (*DeleteContext)(RenderContext *);

    void (*Clear)(LTRect *, uint32, LTVector *);

    LTBOOL (*Start3D)();
    LTBOOL (*End3D)();
    LTBOOL (*IsIn3D)();

    LTBOOL (*StartOptimized2D)();
    void (*EndOptimized2D)();
    LTBOOL (*IsInOptimized2D)();

    LTBOOL (*SetOptimized2DBlend)(LTSurfaceBlend);
    LTBOOL (*GetOptimized2DBlend)(LTSurfaceBlend &);
    LTBOOL (*SetOptimized2DColor)(HLTCOLOR);
    LTBOOL (*GetOptimized2DColor)(HLTCOLOR &);

    int (*RenderScene)(SceneDesc *);
    void (*RenderCommand)(int, char **);

    void *(*GetDirectDrawInterface)(const char *);

    void (*SwapBuffers)(uint32);

    int (*GetInfoFlags)();

    void (*GetScreenFormat)(PFormat *);

    HLTBUFFER (*CreateSurface)(int, int);
    void (*DeleteSurface)(HLTBUFFER);

    void (*GetSurfaceInfo)(HLTBUFFER, uint32 *, uint32 *, int *);

    void *(*LockSurface)(HLTBUFFER);
    void (*UnlockSurface)(HLTBUFFER);

    LTBOOL (*OptimizeSurface)(HLTBUFFER, GenericColor);
    void (*UnoptimizeSurface)(HLTBUFFER);

    LTBOOL (*LockScreen)(int, int, int, int, void **, int *);
    void (*UnlockScreen)();

    void (*BlitToScreen)(BlitRequest *);
    LTBOOL (*WarpToScreen)(BlitRequest *);

    void (*MakeScreenShot)(const char *);
    void (*ReadConsoleVariables)();
    void (*BlitFromScreen)(BlitRequest *);

    uint32 m_dwData_264;
    SharedTexture *m_pEnvMapTexture;
    GlobalPanInfo m_GlobalPanInfo[2];
    LTVector m_vGlobalLightDir;
    LTVector m_vGlobalLightColor;
    float m_fAmbientLight;
    uint32 m_dwCWO_Flags;
};

static_assert(sizeof(void *) == 4, "AVP2 renderer ABI requires a 32-bit build.");
static_assert(offsetof(RenderStruct, Init) == 0x70, "RenderStruct ABI mismatch at Init");
static_assert(offsetof(RenderStruct, Start3D) == 0x90, "RenderStruct ABI mismatch at Start3D");
