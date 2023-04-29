#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"

namespace Rendering::Programs {

struct DepthMap {
    p6::Shader _program;

    GLint uLightSpaceMatrix{};
    GLint uModel{};

    DepthMap()
        : _program{p6::load_shader("../src/Rendering/Programs/DepthMap/simpleDepthShader.vs.glsl", "../src/Rendering/Programs/DepthMap/simpleDepthShader.fs.glsl")}
        , uLightSpaceMatrix(glGetUniformLocation(_program.id(), "uLightSpaceMatrix"))
        , uModel(glGetUniformLocation(_program.id(), "uModel"))
    {}

    void setMatrices(glm::mat4 model, glm::mat4 lightSpace) const
    {
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(lightSpace));
    }
};

} // namespace Rendering::Programs