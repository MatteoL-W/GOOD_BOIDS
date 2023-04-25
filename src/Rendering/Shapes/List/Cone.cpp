#include "Cone.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

Cone::Cone(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::cone_vertices(getRadius(), getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Cone::draw(utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    _shader._program.use();

    auto const  up            = glm::vec3(0.f, 1.f, 0.f);
    auto const  rotationAxis  = glm::cross(up, transformAttributes._velocity);
    float const rotationAngle = glm::acos(glm::dot(up, transformAttributes._velocity));

    auto model = glm::translate(glm::mat4{1}, transformAttributes._position);
    model      = glm::rotate(model, rotationAngle, rotationAxis);

    _shader.setMatrices(model);

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));

    glUseProgram(0);
}

void Cone::drawDepthMap(const utils::TransformAttributes& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    _depthMap._program.use();

    auto const  up            = glm::vec3(0.f, 1.f, 0.f);
    auto const  rotationAxis  = glm::cross(up, transformAttributes._velocity);
    float const rotationAngle = glm::acos(glm::dot(up, transformAttributes._velocity));

    auto model = glm::translate(glm::mat4{1}, transformAttributes._position);
    model      = glm::rotate(model, rotationAngle, rotationAxis);

    _depthMap.setModel(model);
    _depthMap.setLightSpace(lightSpaceMatrix);

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));

    glUseProgram(0);
}

} // namespace Rendering::Shapes