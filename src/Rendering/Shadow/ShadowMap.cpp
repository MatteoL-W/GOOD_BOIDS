#include "ShadowMap.h"
#include <p6/p6.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Rendering::Shadow {

ShadowMap::ShadowMap()
{
    generateDepthTexture();
    attachTextureToFBO();
};

void ShadowMap::bindTextureOnFirstUnit() const
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _depthMapTexture);
}

void ShadowMap::generateDepthTexture()
{
    glGenFramebuffers(1, &_depthMapFBO);

    glGenTextures(1, &_depthMapTexture);
    glBindTexture(GL_TEXTURE_2D, _depthMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _SHADOW_WIDTH, _SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Better shadows
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    float borderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
}

void ShadowMap::attachTextureToFBO() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, _depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _depthMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::renderDepthMap(std::function<void(glm::mat4)> const& renderCastersShadowsFn, Lights::Directional& directional)
{
    glCullFace(GL_FRONT);
    generateLightSpaceMatrix(directional);
    glViewport(0, 0, _SHADOW_WIDTH, _SHADOW_HEIGHT);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _depthMapFBO);

    glClear(GL_DEPTH_BUFFER_BIT);
    renderCastersShadowsFn(_lightSpaceMatrix);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glCullFace(GL_BACK);
}

void ShadowMap::generateLightSpaceMatrix(Lights::Directional& directional)
{
    auto const lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 15.f);
    auto const lightView       = glm::lookAt(directional.getPosition(), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    _lightSpaceMatrix          = lightProjection * lightView;
}

ShadowMap::~ShadowMap()
{
    glDeleteTextures(1, &_depthMapTexture);
    glDeleteFramebuffers(1, &_depthMapFBO);
}

} // namespace Rendering::Shadow