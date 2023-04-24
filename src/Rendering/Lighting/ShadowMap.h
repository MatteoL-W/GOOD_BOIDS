#pragma once

#include <p6/p6.h>
#include "Rendering/Programs/DepthMap.h"

namespace Lighting {

class ShadowMap {
public:
    explicit ShadowMap(glm::vec3 direction);
    void renderDepthMap(std::function<void(glm::mat4)> renderCastersShadowsFn);

    glm::vec3 getDirection() const { return _direction; };
    glm::mat4 getLightSpaceMatrix() const { return lightSpaceMatrix; };

private:
    void defineDepthMap();

private:
    glm::vec3                     _direction;
    Rendering::Programs::DepthMap shader{};

    const unsigned int SHADOW_WIDTH  = 1024;
    const unsigned int SHADOW_HEIGHT = 1024;
    unsigned int       depthMapFBO;
    unsigned int       depthMap;
    glm::mat4          lightSpaceMatrix;
};

} // namespace Light
