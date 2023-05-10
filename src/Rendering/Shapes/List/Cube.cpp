#include "Cube.h"
#include "Rendering/Engine/Mesh.h"
#include "glm/ext/matrix_transform.hpp"

namespace Rendering::Shapes {

Cube::Cube()
    : _model("assets/models/Cube/Cube.gltf")
{}

void Cube::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto modelMatrix = glm::scale(glm::mat4{1}, glm::vec3(_radius));

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
}

} // namespace Rendering::Shapes
