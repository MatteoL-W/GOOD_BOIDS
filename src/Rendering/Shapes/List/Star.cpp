#include "Star.h"
#include <glm/gtx/quaternion.hpp>
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Star::Star(float radius)
    : _radius(radius)
    , _model("assets/models/Star/Star2.gltf")
{}

void Star::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    glCullFace(GL_FRONT);

    auto modelMatrix = glm::translate(glm::mat4{1.f}, transformAttributes._position);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3(_radius));

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