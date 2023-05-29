#include "Ground.h"
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Geometries/geometriesVertices.hpp"

namespace Rendering::Shapes {

Ground::Ground(float radius)
    : _texture("assets/textures/ground.png"), _radius(radius), _vertices(Geometries::generatePlaneVertices()), _mesh(Engine::Mesh{_vertices})
{}

void Ground::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto modelViewMatrix = glm::translate(glm::mat4{1.f}, transformAttributes._position);
    modelViewMatrix      = glm::scale(modelViewMatrix, glm::vec3{_radius});

    _shader._program.use();
    _shader.setMatrices(modelViewMatrix, renderingDatas);

    _texture.bindOnUnit(0);
    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
    Rendering::Engine::Texture::unbind();
}

} // namespace Rendering::Shapes