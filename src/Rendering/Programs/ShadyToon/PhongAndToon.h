#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"
#include "utils/RenderingDatas.h"

namespace Rendering::Programs {

struct PhongAndShadow {
    p6::Shader _program;

    PhongAndShadow()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/ShadyToon/ShadyToon.vs.glsl",
                "../src/Rendering/Programs/ShadyToon/ShadyToon.fs.glsl"
            )}
    {}

    void setMatrices(glm::mat4 model, utils::RenderingDatas& renderingDatas) const
    {
        _program.set("uDiffuseTexture", 0);
        _program.set("uShadowMap", 1);
        _program.set("uProjection", utils::getProjectionMatrix());
        _program.set("uView", Camera::getViewMatrix());
        _program.set("uModel", model);
        _program.set("uLightSpaceMatrix", renderingDatas._lightSpaceMatrix);

        if (renderingDatas._directional)
            renderingDatas._directional->setMatrices(_program);

        for (size_t i = 0; i < renderingDatas._points.size(); i++)
            renderingDatas._points[i].setMatrices(static_cast<unsigned int>(i), _program);
        _program.set("uPointLightsAmount", static_cast<int>(renderingDatas._points.size()));

        _program.set("uViewPow", Camera::getPosition());
    }
};

} // namespace Rendering::Programs