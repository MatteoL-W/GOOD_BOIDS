#include "SkyBox.h"
#include "Rendering/Geometries/geometriesVertices.hpp"

namespace Rendering::Engine {

void SkyBox::setFaces(const std::vector<std::string>& facesPaths)
{
    createTexture(facesPaths);
    createMesh();
}

void SkyBox::createTexture(std::vector<std::string> faces)
{
    glGenTextures(1, &_cubeMapTextureId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTextureId);

    for (unsigned int i = 0; i < faces.size(); i++)
    {
        auto image = p6::load_image_buffer(faces[i]);
        if (image.data())
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, static_cast<int>(image.width()), static_cast<int>(image.height()), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
        else
            throw std::runtime_error("Cubemap undefined");
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void SkyBox::createMesh()
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    auto vertices = Geometries::generateSkyboxVertices();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), reinterpret_cast<void*>(0));
}

void SkyBox::draw()
{
    glCullFace(GL_FRONT); // Cull front-facing triangles
    glFrontFace(GL_CW);   // Set the front face of triangles to counter-clockwise

    glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when values are equal to depth buffer's content

    _skyBoxShader.setMatrices();
    _skyBoxShader._program.use();

    glBindVertexArray(_vao);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _cubeMapTextureId);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);

    glDepthFunc(GL_LESS); // set depth function back to default

    glCullFace(GL_BACK); // Cull back-facing triangles
    glFrontFace(GL_CW);  // Set the front face of triangles to counter-clockwise
}

SkyBox::~SkyBox()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
}

} // namespace Rendering::Engine