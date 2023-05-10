#include "Plane.h"
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Geometries/geometriesVertices.hpp"

namespace Rendering::Shapes {

Plane::Plane(float radius)
    : _radius(radius), _vertices(Rendering::Geometries::plane_vertices()), _mesh(RenderEngine::Mesh{_vertices})
{
    //ToDo: Texture class
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    const auto texture = p6::load_image_buffer("assets/textures/EarthMap.jpg");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    auto modelViewMatrix = glm::translate(glm::mat4{1.f}, transformAttributes._position);
    modelViewMatrix      = glm::scale(modelViewMatrix, glm::vec3{_radius});

    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelViewMatrix, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(modelViewMatrix, renderingDatas._lightSpaceMatrix);
        break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Rendering::Shapes