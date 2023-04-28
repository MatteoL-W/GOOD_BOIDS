#pragma once

#include "Rendering/Cameras/CameraManager.h"
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include <p6/p6.h>

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

    void setLightSpace(glm::mat4 lightSpace) const
    {
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(lightSpace));
    }

    void setModel(glm::mat4 model) const
    {
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
    }
};

} // namespace Rendering::Programs