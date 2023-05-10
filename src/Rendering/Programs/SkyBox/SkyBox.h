#pragma once

#include <p6/p6.h>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct SkyBox {
    p6::Shader _program;

    SkyBox()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/SkyBox/Skybox.vs.glsl",
                "../src/Rendering/Programs/Skybox/Skybox.fs.glsl"
            )}
    {}

    [[maybe_unused]] void setMatrices() const
    {
        auto view = glm::mat4{glm::mat3{Camera::getViewMatrix()}};
        auto MVPMatrix = utils::getProjectionMatrix() * view;

        _program.set("uMVPMatrix", MVPMatrix);
        _program.set("skybox", 0);
    }
};

} // namespace Rendering::Programs