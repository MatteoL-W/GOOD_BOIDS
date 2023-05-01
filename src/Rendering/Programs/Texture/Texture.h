#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

// ToDo : Same setMatrices for every 3D.vs.glsl users.

struct Texture {
    p6::Shader _program;

    Texture()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/3D.vs.glsl",
                "../src/Rendering/Programs/Texture/texture.fs.glsl"
            )}
    {}

    [[maybe_unused]] void setMatrices(glm::mat4 model) const
    {
        auto modelViewMatrix = Camera::getViewMatrix() * model;
        auto normalMatrix    = glm::transpose(glm::inverse(modelViewMatrix));

        _program.set("uMVMatrix", modelViewMatrix);
        _program.set("uMVPMatrix", utils::getProjectionMatrix() * modelViewMatrix);
        _program.set("uNormalMatrix", normalMatrix);
    }
};

} // namespace Rendering::Programs