#pragma once

#include "../lt_renderer_abi.h"
#include <cmath>

static LTVector ObjectLocalToCamera(const SceneDesc *scene, const LTObjectCompat &o, LTVector local)
    {
        local = local * LTVector {o.m_vScale.x, o.m_vScale.y, o.m_vScale.z};
        LTRotation oq{o.m_rRot.x, o.m_rRot.y, o.m_rRot.z, o.m_rRot.w};
        LTVector world = oq.Rotate(local) + LTVector {o.m_vPos.x, o.m_vPos.y, o.m_vPos.z};

        if (o.m_dwFlags & FLAG_REALLYCLOSE)
            return world;

        LTVector rel = world - LTVector {scene->m_vPos.x, scene->m_vPos.y, scene->m_vPos.z};
        LTRotation cq{scene->m_rRotation.x, scene->m_rRotation.y,
                      scene->m_rRotation.z, scene->m_rRotation.w};
        return cq.Conjugate().Rotate(rel);
    }