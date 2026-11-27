#pragma once

#include "../../lt_renderer_abi.h"
#include <cstddef>

struct WorldTreeCompat;

enum NodeObjArrayCompat : int32
{
    NOA_Objects_Compat = 0,
    NOA_Lights_Compat = 1,
    NOA_VisContainers_Compat = 2
};

using WTObjCallbackCompat = void (__cdecl*)(void* pObj,void* pData);
using AddObjectsFnCompat = void (__cdecl*)(LTLinkCompat* pLink,LTObjectCompat*** pppBuffer,uint32* pCounter);
using IterateLeafCBCompat = void (__cdecl*)(LeafCompat* pLeaf,void* pData);
using PortalTestFnCompat = int32 (__cdecl*)(void* pPortal);
using NodeFilterFnCompat = int32 (__cdecl*)(void* pNode);

struct VisQueryRequestCompat
{
    int32 m_eObjArray;
    LTVector m_vViewpoint;
    float m_fViewRadius;
    WTObjCallbackCompat m_ObjectCB;
    AddObjectsFnCompat m_AddObjects;
    void* m_pUserData;
    IterateLeafCBCompat m_LeafCB;
    PortalTestFnCompat m_PortalTest;
    NodeFilterFnCompat m_NodeFilterFn;
    LTVector m_vMin;
    LTVector m_vMax;
    WorldTreeCompat* m_pTree;
};
static_assert(sizeof(VisQueryRequestCompat)==72,"VisQueryRequestCompat size mismatch");

struct FindObjInfoCompat
{
    WorldTreeCompat* m_pTree;
    int32 m_eObjArray;
    LTVector m_vMin;
    LTVector m_vMax;
    LTVector m_vViewpoint;
    WTObjCallbackCompat m_CB;
    void* m_pCBUser;
};

using FindObjectsInBox2Compat = void (__fastcall*)(WorldTreeCompat*,void*,FindObjInfoCompat*);

struct WorldTreeVTableCompat
{
    void* fn0;
    void* FindObjectsInBox;
    FindObjectsInBox2Compat FindObjectsInBox2;
    void* fn3;
    void* IntersectSegment;
    void (__fastcall* DoVisQuery)(WorldTreeCompat* pTree,void* notUsed,VisQueryRequestCompat* pRequest);
};

struct WorldTreeCompat
{
    WorldTreeVTableCompat* m_pVTable;
    uint8 m_pad4_115[112];
    LTLinkCompat m_AlwaysVisObjects;
};
static_assert(offsetof(WorldTreeCompat,m_AlwaysVisObjects)==116,"WorldTree AlwaysVis offset mismatch");
