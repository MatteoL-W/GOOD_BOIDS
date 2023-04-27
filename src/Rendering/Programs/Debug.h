#pragma once

#include <p6/p6.h>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct Debug {
    p6::Shader _program;

    GLint near_plane{};
    GLint far_plane{};

    Debug()
        : _program{p6::load_shader("../src/Rendering/Programs/Shaders/debug.vs.glsl", "../src/Rendering/Programs/Shaders/debug.fs.glsl")}
        , near_plane(glGetUniformLocation(_program.id(), "near_plane"))
        , far_plane(glGetUniformLocation(_program.id(), "far_plane"))
    {}

    void setMatrices() const
    {
        glUniform1f(near_plane, .1f);
        glUniform1f(far_plane, 100.f);
    }
};

} // namespace Rendering::Programs