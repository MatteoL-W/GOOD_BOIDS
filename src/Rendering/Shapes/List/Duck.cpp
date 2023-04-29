#include "Duck.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _model("assets/models/Duck/Duck.gltf")
{}


void Duck::draw(utils::RenderType renderType, utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix      = glm::scale(modelMatrix, glm::vec3(0.01f));

    switch (renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelMatrix, lightSpaceMatrix);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(modelMatrix, lightSpaceMatrix);
        break;
    }
    
    _model.draw();

    glUseProgram(0);
}

} // namespace Rendering::Shapes