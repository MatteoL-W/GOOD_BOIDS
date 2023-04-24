#include "Plane.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

// ToDo: Clean constructor and use radius
Plane::Plane(float radius)
    : _radius(radius), _vertices(std::vector<Rendering::Geometries::Vertex3D>{{{-10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 0.0f}}, {{10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 0.0f}}, {{10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 10.0f}},{{-10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 0.0f}}, {{10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 10.0f}}, {{-10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 10.0f}}}), _mesh(RenderEngine::Mesh{_vertices})
{}

void Plane::draw(utils::TransformAttributes const& transformAttributes) const
{
    // ToDo: Use transformAttributes
    _shader._program.use();
    _shader.setMatrices(glm::mat4{1});
    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
}

} // namespace Rendering::Shapes