#include "Sphere.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Sphere::Sphere(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::sphere_vertices(getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Sphere::draw(utils::TransformAttributes const& transformAttributes) const
{
    _shader._program.use();

    auto transformation = glm::translate(glm::mat4{1}, transformAttributes._position);
    _shader.setMatrices(transformation);

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));

    glUseProgram(0);
}

void Sphere::drawDepthMap(const utils::TransformAttributes& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    _depthMap._program.use();

    auto model = glm::translate(glm::mat4{1}, transformAttributes._position);

    _depthMap.setModel(model);
    _depthMap.setLightSpace(lightSpaceMatrix);

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));

    glUseProgram(0);
}

} // namespace Rendering::Shapes