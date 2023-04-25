#pragma once

#include <p6/p6.h>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct Texture {
    p6::Shader _program;

    GLint uMVPMatrix{};
    GLint uMVMatrix{};
    GLint uNormalMatrix{};

    Texture()
        : _program{p6::load_shader("../src/Rendering/Programs/Shaders/3D.vs.glsl", "../src/Rendering/Programs/Shaders/texture.fs.glsl")}
        , uMVPMatrix(glGetUniformLocation(_program.id(), "uMVPMatrix"))
        , uMVMatrix(glGetUniformLocation(_program.id(), "uMVMatrix"))
        , uNormalMatrix(glGetUniformLocation(_program.id(), "uNormalMatrix"))
    {}

    void setMatrices(glm::mat4 model) const
    {
        auto modelViewMatrix = Camera::getViewMatrix() * model;
        auto normalMatrix    = glm::transpose(glm::inverse(modelViewMatrix));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(utils::getProjectionMatrix() * modelViewMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
};

} // namespace Rendering::Programs