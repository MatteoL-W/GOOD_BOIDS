#include "Drop.h"
#include <glm/gtx/quaternion.hpp>
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Drop::Drop()
    : _radius(.01f)
    , _model(Engine::Model{"assets/models/Drop/scene.gltf"})
{}

void Drop::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto const rotationQuaternion = glm::rotation(glm::vec3{0.f, 0.f, 1.f}, glm::vec3{0.f, 1.f, 0.f});

    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix      = modelMatrix * glm::mat4_cast(rotationQuaternion);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3{_radius});

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
}

} // namespace Rendering::Shapes