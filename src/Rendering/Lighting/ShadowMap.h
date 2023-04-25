#pragma once

#include <p6/p6.h>
#include "Rendering/Programs/DepthMap.h"

namespace Lighting {

class ShadowMap {
public:
    explicit ShadowMap();
    void renderDepthMap(std::function<void(glm::mat4)> renderCastersShadowsFn);

private:
    void defineDepthMap();

private:
    Rendering::Programs::DepthMap _shader;

    const unsigned int SHADOW_WIDTH  = 2048;
    const unsigned int SHADOW_HEIGHT = 2048;
    unsigned int       depthMapFBO;
    unsigned int       depthMap;
    glm::mat4          lightSpaceMatrix;
};

}  // namespace Lighting
