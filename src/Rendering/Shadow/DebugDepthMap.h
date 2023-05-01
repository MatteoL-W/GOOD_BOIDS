#pragma once

#include <p6/p6.h>
#include "Rendering/Programs/DebugDepthMap/Debug.h"

namespace Rendering::Shadow {

class DebugDepthMap {
public:
    DebugDepthMap();
    void render(p6::Context& ctx, GLuint depthMapTexture);

private:
    Rendering::Programs::Debug _shader{};
    GLuint                     _quadVAO{};
    GLuint                     _quadVBO{};
};

} // namespace Rendering::Shadow