#include "Fence.h"
#include <glm/gtx/quaternion.hpp>
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Fence::Fence()
    : _model(Engine::Model{"assets/models/Fence/fence.gltf"})
{}

void Fence::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    glCullFace(GL_FRONT);

    auto modelMatrix = glm::translate(glm::mat4{1.f}, transformAttributes._position);
    auto rotation    = glm::rotate(glm::mat4{1}, glm::radians(90.f), glm::vec3{0.f, 1.f, 0.f});
    drawWithRightShader(modelMatrix, renderingDatas);

    modelMatrix = modelMatrix * rotation;
    drawWithRightShader(modelMatrix, renderingDatas);

    modelMatrix = modelMatrix * rotation;
    drawWithRightShader(modelMatrix, renderingDatas);

    modelMatrix = modelMatrix * rotation;
    drawWithRightShader(modelMatrix, renderingDatas);

    glCullFace(GL_BACK);
    glUseProgram(0);
}

void Fence::drawWithRightShader(glm::mat4& model, utils::RenderingDatas& renderingDatas) const
{
    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(model, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(model, renderingDatas._lightSpaceMatrix);
        break;
    }

    _model.draw();
}

} // namespace Rendering::Shapes