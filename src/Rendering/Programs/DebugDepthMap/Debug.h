#pragma once

#include "Rendering/Cameras/CameraManager.h"
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include <p6/p6.h>
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct Debug {
    p6::Shader _program;

    GLint near_plane{};
    GLint far_plane{};

    Debug()
        : _program{p6::load_shader("../src/Rendering/Programs/DebugDepthMap/debug.vs.glsl", "../src/Rendering/Programs/DebugDepthMap/debug.fs.glsl")}
        , near_plane(glGetUniformLocation(_program.id(), "near_plane"))
        , far_plane(glGetUniformLocation(_program.id(), "far_plane"))
    {}

    void setNearAndFar(float nearLimit, float farLimit) const
    {
        glUniform1f(near_plane, nearLimit);
        glUniform1f(far_plane, farLimit);
    }
};

} // namespace Rendering::Programs