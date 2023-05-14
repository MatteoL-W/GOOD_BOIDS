#include "Sphere.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Sphere::Sphere(float radius)
    : _radius(radius), _vertices(Geometries::sphere_vertices(1.f, 32, 16)), _mesh(Engine::Mesh{_vertices})
{}

void Sphere::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3{_radius});

    switch (renderingDatas._renderType)
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