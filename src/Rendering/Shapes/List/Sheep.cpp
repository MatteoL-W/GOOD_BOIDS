#include <glm/gtx/quaternion.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Sheep.h"

namespace Rendering::Shapes {

Sheep::Sheep()
    : _radius(0.2f)
    , _model("assets/models/Sheep/Sheep.gltf")
{}

void Sheep::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    glCullFace(GL_FRONT);

    auto const rotationFrontQuaternion = glm::rotation(glm::vec3(0.f, -1.f, 0.f), glm::normalize(transformAttributes._velocity));
    auto const rotationLeftQuaternion = glm::rotation(glm::vec3(1.f, 0.f, 0.f), glm::normalize(transformAttributes._left));

    auto modelMatrix = glm::translate(glm::mat4{1.f}, transformAttributes._position);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3(_radius));
    modelMatrix      = modelMatrix * glm::mat4_cast(rotationFrontQuaternion);
    modelMatrix      = modelMatrix * glm::mat4_cast(rotationLeftQuaternion);

    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelMatrix, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(modelMatrix, renderingDatas._lightSpaceMatrix);
        break;
    }

    _model.draw();

    glUseProgram(0);
    glCullFace(GL_BACK);
}

} // namespace Rendering::Shapes