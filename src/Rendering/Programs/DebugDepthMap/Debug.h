#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"

namespace Rendering::Programs {

struct Debug {
    p6::Shader _program;
    Debug()
        : _program{
            p6::load_shader(
                "../src/Rendering/Programs/DebugDepthMap/debug.vs.glsl",
                "../src/Rendering/Programs/DebugDepthMap/debug.fs.glsl"
            )}
    {}

    void setNearAndFar(float nearLimit, float farLimit) const
    {
        _program.set("uNearPlane", nearLimit);
        _program.set("uFarPlane", farLimit);
    }
};

} // namespace Rendering::Programs