#pragma once

#include <p6/p6.h>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"

namespace Rendering::Programs {

struct DepthMap {
    p6::Shader _program;

    GLint uLightSpaceMatrix{};
    GLint uModel{};

    DepthMap()
        : _program{p6::load_shader("../src/Rendering/Programs/Shaders/simpleDepthShader.vs.glsl", "../src/Rendering/Programs/Shaders/simpleDepthShader.fs.glsl")}
        , uLightSpaceMatrix(glGetUniformLocation(_program.id(), "uLightSpaceMatrix"))
        , uModel(glGetUniformLocation(_program.id(), "uModel"))
    {}

    void setMatrices(glm::mat4 lightSpaceMatrix, glm::mat4 modelMatrix) const
    {
        // What about uModel ? We gave it a mat4{1}.
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    }
};

} // namespace Rendering::Programs