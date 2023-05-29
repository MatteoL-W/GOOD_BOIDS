#include "House.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

House::House()
    : _radius(1.f)
    , _model(Engine::Model{"assets/models/House/house3.gltf"})
{}

void House::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    glCullFace(GL_FRONT);

    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3{_radius});
    modelMatrix = glm::scale(modelMatrix, glm::vec3{0.5f});

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

    glCullFace(GL_BACK);
    glUseProgram(0);
}

} // namespace Rendering::Shapes