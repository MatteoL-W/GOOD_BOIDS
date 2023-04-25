#include "Duck.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _model("assets/models/Duck/Duck.gltf")
{}

void Duck::draw(utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    _shader._program.use();

    auto model = glm::translate(glm::mat4{1}, transformAttributes._position);
    model      = glm::scale(model, glm::vec3(0.01f));

    _shader.setMatrices(model, lightSpaceMatrix);

    _model.draw();

    glUseProgram(0);
}

void Duck::drawDepthMap(const utils::TransformAttributes& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    _depthMap._program.use();

    auto model = glm::translate(glm::mat4{1}, transformAttributes._position);
    model      = glm::scale(model, glm::vec3(0.01f));

    _depthMap.setModel(model);
    _depthMap.setLightSpace(lightSpaceMatrix);

    _model.draw();

    glUseProgram(0);
}

} // namespace Rendering::Shapes