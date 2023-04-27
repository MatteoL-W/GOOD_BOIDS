#include "Plane.h"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

// ToDo: Clean constructor and use radius
Plane::Plane(float radius)
    : _radius(radius), _vertices(std::vector<Rendering::Geometries::Vertex3D>{{{-30.0f, 0.0f, -30.0f}, {0.0f, 30.0f, 0.0f}, {0.0f, 0.0f}}, {{30.0f, 0.0f, -30.0f}, {0.0f, 30.0f, 0.0f}, {30.0f, 0.0f}}, {{30.0f, 0.0f, 30.0f}, {0.0f, 30.0f, 0.0f}, {30.0f, 30.0f}}, {{-30.0f, 0.0f, -30.0f}, {0.0f, 30.0f, 0.0f}, {0.0f, 0.0f}}, {{30.0f, 0.0f, 30.0f}, {0.0f, 30.0f, 0.0f}, {30.0f, 30.0f}}, {{-30.0f, 0.0f, 30.0f}, {0.0f, 30.0f, 0.0f}, {0.0f, 30.0f}}}), _mesh(RenderEngine::Mesh{_vertices})
{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    const auto texture = p6::load_image_buffer("assets/textures/EarthMap.jpg");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Plane::draw(utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const
{
    // ToDo: Use transformAttributes
    _shader._program.use();
    _shader.setMatrices(glm::mat4{1}, lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    _mesh.draw(static_cast<GLsizei>(_vertices.size()));
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace Rendering::Shapes