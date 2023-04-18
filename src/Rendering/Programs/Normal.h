#pragma once

#include <p6/p6.h>
#include "Rendering/Cameras/CameraManager.h"

namespace Rendering::Programs {

struct Normal {
    p6::Shader _program;

    GLint uMVPMatrix{};
    GLint uMVMatrix{};
    GLint uNormalMatrix{};

    Normal()
        : _program{p6::load_shader("../src/Rendering/Programs/Shaders/3D.vs.glsl", "../src/Rendering/Programs/Shaders/normal.fs.glsl")}
        , uMVPMatrix(glGetUniformLocation(_program.id(), "uMVPMatrix"))
        , uMVMatrix(glGetUniformLocation(_program.id(), "uMVMatrix"))
        , uNormalMatrix(glGetUniformLocation(_program.id(), "uNormalMatrix"))
    {}

    void setMatrices(glm::mat4 transformation, float aspect_ratio) const
    {
        auto modelViewMatrix = Camera::getViewMatrix();
        modelViewMatrix      = modelViewMatrix * transformation;

        auto projectionMatrix = glm::perspective(glm::radians(70.f), aspect_ratio, .1f, 100.f);
        auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));
    }
};

} // namespace Rendering::Programs