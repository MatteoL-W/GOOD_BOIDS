#include "Directional.h"
#include <p6/p6.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Light {

Directional::Directional(glm::vec3 direction)
    : _direction(direction)
{
    defineDepthMap();
};

void Directional::defineDepthMap()
{
    // First we'll generate a framebuffer object for rendering the depth map:
    glGenFramebuffers(1, &depthMapFBO);

    // Next we create a 2D texture that we'll use as the framebuffer's depth buffer:
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // With the generated depth texture we can attach it as the framebuffer's depth buffer (FBO)
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);

    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Directional::renderDepthMap(std::function<void(glm::mat4)> renderCastersShadowsFn)
{
    // 1. first render to depth map
    float     near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView       = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lightSpaceMatrix          = lightProjection * lightView;

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, depthMapFBO);
    glpp::viewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT); // Width/height of shadow map

    glClear(GL_DEPTH_BUFFER_BIT);
    renderCastersShadowsFn(lightSpaceMatrix);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

} // namespace Light