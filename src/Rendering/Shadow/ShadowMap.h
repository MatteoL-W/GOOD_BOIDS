#pragma once

#include <p6/p6.h>
#include "Rendering/Programs/DepthMap/DepthMap.h"

namespace Rendering::Lighting {

class ShadowMap {
public:
    explicit ShadowMap();
    ~ShadowMap();
    void renderDepthMap(std::function<void(glm::mat4)> const& renderCastersShadowsFn);

    glm::mat4 getLightSpaceMatrix() { return _lightSpaceMatrix; };
    GLuint    getDepthMapTextureId() const { return _depthMapTexture; };
    void      bindTextureOnFirstUnit() const;

private:
    void generateDepthTexture();
    void generateLightSpaceMatrix();
    void attachTextureToFBO() const;

private:
    const unsigned int _SHADOW_WIDTH  = 2048;
    const unsigned int _SHADOW_HEIGHT = 2048;

    Rendering::Programs::DepthMap _shader{};

    GLuint    _depthMapTexture{};
    GLuint    _depthMapFBO{};
    glm::mat4 _lightSpaceMatrix{};
};

} // namespace Rendering::Lighting
