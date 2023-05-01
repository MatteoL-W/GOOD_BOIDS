#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Rendering/Cameras/CameraManager.h"
#include "utils/ProjectionMatrixHandler.h"
#include "utils/RenderingDatas.h"

namespace Rendering::Programs {

struct PhongAndShadow {
    p6::Shader _program;

    GLint uDiffuseTexture{};
    GLint uShadowMap{};
    GLint uProjection{};
    GLint uView{};
    GLint uModel{};
    GLint uLightSpaceMatrix{};
    GLint uDirLightPos{}; // In order to draw shadows!
    GLint uViewPos{};

    PhongAndShadow()
        : _program{p6::load_shader("../src/Rendering/Programs/ShadyPhong/shadowRendering.vs.glsl", "../src/Rendering/Programs/ShadyPhong/shadowRendering.fs.glsl")}
        , uDiffuseTexture(glGetUniformLocation(_program.id(), "uDiffuseTexture"))
        , uShadowMap(glGetUniformLocation(_program.id(), "uShadowMap"))
        , uProjection(glGetUniformLocation(_program.id(), "uProjection"))
        , uView(glGetUniformLocation(_program.id(), "uView"))
        , uModel(glGetUniformLocation(_program.id(), "uModel"))
        , uLightSpaceMatrix(glGetUniformLocation(_program.id(), "uLightSpaceMatrix"))
        , uDirLightPos(glGetUniformLocation(_program.id(), "dirLight.position"))
        , uViewPos(glGetUniformLocation(_program.id(), "uViewPos"))
    {}

    void setMatrices(glm::mat4 model, utils::RenderingDatas& renderingDatas) const
    {
        glUniform1i(uDiffuseTexture, 0);
        glUniform1i(uShadowMap, 1);
        glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(utils::getProjectionMatrix()));
        glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(Camera::getViewMatrix()));
        glUniformMatrix4fv(uModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uLightSpaceMatrix, 1, GL_FALSE, glm::value_ptr(renderingDatas._lightSpaceMatrix));

        renderingDatas._directional->setMatrices(_program.id());

        // ToDo: Move in classes
        glUniform1i(glGetUniformLocation(_program.id(), "pointLightsAmount"), 1);
        glUniform3fv(glGetUniformLocation(_program.id(), "pointLights[0].position"), 1, glm::value_ptr(glm::vec3(-2.f, .1f, .0f)));
        glUniform3fv(glGetUniformLocation(_program.id(), "pointLights[0].ambient"), 1, glm::value_ptr(glm::vec3(0.1f)));
        glUniform3fv(glGetUniformLocation(_program.id(), "pointLights[0].diffuse"), 1, glm::value_ptr(glm::vec3(0.4f)));
        glUniform3fv(glGetUniformLocation(_program.id(), "pointLights[0].specular"), 1, glm::value_ptr(glm::vec3(1.f)));
        glUniform1f(glGetUniformLocation(_program.id(), "pointLights[0].constant"), 1.0f);
        glUniform1f(glGetUniformLocation(_program.id(), "pointLights[0].linear"), .09f);
        glUniform1f(glGetUniformLocation(_program.id(), "pointLights[0].quadratic"), .032f);

        glUniform3fv(uViewPos, 1, glm::value_ptr(Camera::getPosition()));
    }
};

} // namespace Rendering::Programs