#include "Sphere.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Sphere::Sphere(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::sphere_vertices(getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Sphere::draw(utils::RenderType renderType, utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);

    switch (renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelMatrix);
        break;
    case utils::RenderType::DepthMap: break;
    }

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
    glUseProgram(0);
}

} // namespace Rendering::Shapes