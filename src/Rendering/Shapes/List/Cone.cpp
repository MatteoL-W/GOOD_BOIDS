#include "Cone.h"
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Programs/ShadyPhong/PhongAndShadow.h"

namespace Rendering::Shapes {

Cone::Cone(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::cone_vertices(getRadius(), getRadius(), 32, 16)), _mesh(RenderEngine::Mesh{_vertices})
{}

void Cone::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto const  up            = glm::vec3(0.f, 1.f, 0.f);
    auto const  rotationAxis  = glm::cross(up, transformAttributes._velocity);
    float const rotationAngle = glm::acos(glm::dot(up, transformAttributes._velocity));

    auto modelMatrix = glm::translate(glm::mat4{1}, transformAttributes._position);
    modelMatrix      = glm::rotate(modelMatrix, rotationAngle, rotationAxis);

    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelMatrix, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(modelMatrix, renderingDatas._lightSpaceMatrix);
        break;
    }

    _mesh.draw(static_cast<GLsizei>(_vertices.size()));

    glUseProgram(0);
}

} // namespace Rendering::Shapes