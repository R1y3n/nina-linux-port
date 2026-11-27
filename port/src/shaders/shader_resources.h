#pragma once

#include "resources/resource.h"

#include <string>

namespace avp2::render
{
    enum class ShaderResourceId : int
    {
        RendererQuadVertex = IDR_SHADER_RENDERER_QUAD_VERT,
        RendererQuadFragment = IDR_SHADER_RENDERER_QUAD_FRAG,
        ScenePostVertex = IDR_SHADER_SCENE_POST_VERT,
        ScenePostFragment = IDR_SHADER_SCENE_POST_FRAG,
        FullscreenVertex = IDR_SHADER_FULLSCREEN_VERT,
        SsaoFragment = IDR_SHADER_SSAO_FRAG,
        SsrFragment = IDR_SHADER_SSR_FRAG,
        BlurFragment = IDR_SHADER_BLUR_FRAG,
        SsaoCompositeFragment = IDR_SHADER_SSAO_COMPOSITE_FRAG,
        SsrCompositeFragment = IDR_SHADER_SSR_COMPOSITE_FRAG,
        QualityDebugFragment = IDR_SHADER_QUALITY_DEBUG_FRAG,
        BloomExtractFragment = IDR_SHADER_BLOOM_EXTRACT_FRAG,
        BloomBlurFragment = IDR_SHADER_BLOOM_BLUR_FRAG,
        ExposureFragment = IDR_SHADER_EXPOSURE_FRAG,
        ExposureCompositeFragment = IDR_SHADER_EXPOSURE_COMPOSITE_FRAG,
        FxVertex = IDR_SHADER_FX_VERT,
        FxFragment = IDR_SHADER_FX_FRAG,
        ModelBatchVertex = IDR_SHADER_MODEL_BATCH_VERT,
        ModelBatchFragment = IDR_SHADER_MODEL_BATCH_FRAG,
        ModelLegacyVertex = IDR_SHADER_MODEL_LEGACY_VERT,
        ModelLegacyFragment = IDR_SHADER_MODEL_LEGACY_FRAG,
        CharacterShadowVertex = IDR_SHADER_CHARACTER_SHADOW_VERT,
        CharacterShadowFragment = IDR_SHADER_CHARACTER_SHADOW_FRAG,
        SpriteVertex = IDR_SHADER_SPRITE_VERT,
        SpriteFragment = IDR_SHADER_SPRITE_FRAG,
        LightmapCompute = IDR_SHADER_LIGHTMAP_COMP,
        WorldVertex = IDR_SHADER_WORLD_VERT,
        WorldFragment = IDR_SHADER_WORLD_FRAG,
    };

    class ShaderResourceLoader final
    {
    public:
        ShaderResourceLoader() = delete;

        static bool Load(ShaderResourceId id, std::string &source);
    };
}
