#include "Cone.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Cone::Cone(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::cone_vertices(getRadius(), getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Cone::draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes, bool isDepthRendering, glm::mat4 lightSpaceMatrix) const
{
    if (isDepthRendering)
        _depthMap._program.use();
    else
        _shader._program.use();

    auto const  up            = glm::vec3(0.f, 1.f, 0.f);
    auto const  rotationAxis  = glm::cross(up, transformAttributes._velocity);
    float const rotationAngle = glm::acos(glm::dot(up, transformAttributes._velocity));

    auto transformation = Camera::getViewMatrix();
    transformation      = glm::translate(transformation, transformAttributes._position);
    transformation      = glm::rotate(transformation, rotationAngle, rotationAxis);

    if (isDepthRendering)
        _depthMap.setMatrices(lightSpaceMatrix, transformation);
    else
        _shader.setMatrices(transformation, ctx.aspect_ratio());


    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
}

} // namespace Rendering::Shapes