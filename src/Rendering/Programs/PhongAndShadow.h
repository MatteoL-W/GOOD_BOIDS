#pragma once

#include <p6/p6.h>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"

namespace Rendering::Programs {

struct PhongAndShadow {
    p6::Shader _program;

    GLint uProjection{};
    GLint uView{};
    GLint uModel{};
    GLint uLightSpaceMatrix{};
    GLint uLightPos{};
    GLint uViewPos{};

    PhongAndShadow()
        : _program{p6::load_shader("../src/Rendering/Programs/Shaders/shadowRendering.vs.glsl", "../src/Rendering/Programs/Shaders/shadowRendering.fs.glsl")}
        , uProjection(glGetUniformLocation(_program.id(), "projection"))
        , uView(glGetUniformLocation(_program.id(), "view"))
        , uModel(glGetUniformLocation(_program.id(), "model"))
        , uLightSpaceMatrix(glGetUniformLocation(_program.id(), "lightSpaceMatrix"))
        , uLightPos(glGetUniformLocation(_program.id(), "lightPos"))
        , uViewPos(glGetUniformLocation(_program.id(), "viewPos"))
    {}

    void setMatrices(glm::mat4 lightSpaceMatrix, glm::mat4 modelMatrix) const
    {
        // What about uModel ?
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(modelMatrix));
    }
};

} // namespace Rendering::Programs