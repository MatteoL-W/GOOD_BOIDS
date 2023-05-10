#include "Cube.h"
#include "Rendering/Engine/Mesh.h"
#include "glm/ext/matrix_transform.hpp"

namespace Rendering::Shapes {

Cube::Cube(float radius)
    : _radius(radius), _model{"assets/models/Cube/Cube.gltf"}
{}

void Cube::draw() const
{
    auto modelMatrix = glm::scale(glm::mat4{1}, glm::vec3(_radius));

    _shader._program.use();
    _shader.setMatrices(modelMatrix);

    _model.draw();
}

} // namespace Rendering::Shapes
