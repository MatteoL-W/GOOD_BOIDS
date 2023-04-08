#include "Sphere.h"

#include "Utils/Mesh.h"

namespace Shapes::ThreeDimensions {

Sphere::Sphere(float radius)
    : _radius(radius), _vertices(glimac::sphere_vertices(1.f, 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Sphere::draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes) const
{
    _shader._program.use();

    auto modelViewMatrix = glm::translate(glm::mat4{1}, glm::vec3(0.f, 0.f, -5.f));
    modelViewMatrix      = glm::translate(modelViewMatrix, transformAttributes._position);
    modelViewMatrix      = glm::scale(modelViewMatrix, glm::vec3{getRadius()});

    auto projectionMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), .1f, 100.f);
    auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

    glUniformMatrix4fv(_shader.uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(_shader.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
    glUniformMatrix4fv(_shader.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    glBindVertexArray(_mesh.getVao());
    glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
    glBindVertexArray(0);
}

} // namespace Shapes::ThreeDimensions