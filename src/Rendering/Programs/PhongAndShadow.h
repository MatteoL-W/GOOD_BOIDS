#pragma once

#include <p6/p6.h>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

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

    void setMatrices(glm::mat4 model, glm::mat4 lightSpaceMatrix) const
    {
        glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(utils::getProjectionMatrix()));
        glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(Camera::getViewMatrix()));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
        glUniform3fv(uLightPos, 1, glm::value_ptr(glm::vec3(0.f, 10.0f, 0.0f))); // ToDo
        glUniform3fv(uViewPos, 1, glm::value_ptr(Camera::getPosition()));
    }
};

} // namespace Rendering::Programs