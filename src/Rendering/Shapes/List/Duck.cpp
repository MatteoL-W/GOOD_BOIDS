#include "Duck.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _model("assets/models/Duck/Duck.gltf")
{}

void Duck::draw(utils::TransformAttributes const& transformAttributes) const
{
    _shader._program.use();

    auto transformation = glm::translate(glm::mat4{1}, transformAttributes._position);
    transformation      = glm::scale(transformation, glm::vec3(0.01f));

    _shader.setMatrices(transformation);

    _model.draw();
}

} // namespace Rendering::Shapes