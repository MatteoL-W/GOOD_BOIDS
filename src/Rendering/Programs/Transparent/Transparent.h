#pragma once

#include <p6/p6.h>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct Transparent {
    p6::Shader _program;

    Transparent()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/3D.vs.glsl",
                "../src/Rendering/Programs/Transparent/transparent.fs.glsl"
            )}
    {}

    void setMatrices(glm::mat4 model) const
    {
        auto modelViewMatrix = Camera::getViewMatrix() * model;
        auto normalMatrix    = glm::transpose(glm::inverse(modelViewMatrix));

        _program.set("uMVMatrix", modelViewMatrix);
        _program.set("uMVPMatrix", utils::getProjectionMatrix() * modelViewMatrix);
        _program.set("uNormalMatrix", normalMatrix);
    }
};

} // namespace Rendering::Programs