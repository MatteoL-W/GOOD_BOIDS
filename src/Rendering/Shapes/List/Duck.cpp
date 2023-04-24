#include "Duck.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _model("assets/models/Duck/Duck.gltf")
{}

void Duck::draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes, bool isDepthRendering, glm::mat4 lightSpaceMatrix) const
{
    if (isDepthRendering)
        _depthMap._program.use();
    else
        _shader._program.use();

    auto transformation = glm::translate(glm::mat4{1}, transformAttributes._position);
    transformation      = glm::scale(transformation, glm::vec3(0.01f));

    if (isDepthRendering)
        _depthMap.setMatrices(lightSpaceMatrix, transformation);
    else
        _shader.setMatrices(transformation, ctx.aspect_ratio());

    _model.draw();
}

} // namespace Rendering::Shapes