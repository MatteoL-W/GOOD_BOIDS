#include "Duck.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _LODHandler(
        {Model{"assets/models/Duck/Duck.gltf"},
         Model{"assets/models/Duck/DuckMQ.gltf"},
         Model{"assets/models/Duck/DuckLQ.gltf"}},
        10.f
    )
{}

void Duck::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    glCullFace(GL_FRONT);
    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3(0.01f));

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

    _LODHandler.drawCorrespondingModel(
        glm::distance(Camera::getPosition(), transformAttributes._position)
    );

    glUseProgram(0);
    glCullFace(GL_BACK);
}

} // namespace Rendering::Shapes