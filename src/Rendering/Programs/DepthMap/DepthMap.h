#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"

namespace Rendering::Programs {

struct DepthMap {
    p6::Shader _program;

    DepthMap()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/DepthMap/simpleDepthShader.vs.glsl",
                "../src/Rendering/Programs/DepthMap/simpleDepthShader.fs.glsl"
            )}
    {}

    void setMatrices(glm::mat4 model, glm::mat4 lightSpace) const
    {
        _program.set("uModel", model);
        _program.set("uLightSpaceMatrix", lightSpace);
    }
};

} // namespace Rendering::Programs