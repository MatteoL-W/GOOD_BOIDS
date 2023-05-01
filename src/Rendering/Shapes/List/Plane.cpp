#include "Plane.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

// ToDo: Clean constructor and use radius
Plane::Plane(float radius)
    : _radius(radius), _vertices(std::vector<Rendering::Geometries::Vertex3D>{{{-10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 0.0f}}, {{10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 0.0f}}, {{10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 10.0f}}, {{-10.0f, 0.0f, -10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 0.0f}}, {{10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {10.0f, 10.0f}}, {{-10.0f, 0.0f, 10.0f}, {0.0f, 10.0f, 0.0f}, {0.0f, 10.0f}}}), _mesh(RenderEngine::Mesh{_vertices})
{
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    const auto texture = p6::load_image_buffer("assets/textures/EarthMap.jpg");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::draw([[maybe_unused]] utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    // ToDo: Use transformAttributes
    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(glm::mat4{1}, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(glm::mat4{1}, renderingDatas._lightSpaceMatrix);
        break;
    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Rendering::Shapes