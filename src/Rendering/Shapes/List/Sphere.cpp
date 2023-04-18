#include "Sphere.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Sphere::Sphere(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::sphere_vertices(getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Sphere::draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes) const
{
    _shader._program.use();

    auto transformation = glm::translate(glm::mat4{1}, transformAttributes._position);
    _shader.setMatrices(transformation, ctx.aspect_ratio());

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
}

} // namespace Rendering::Shapes