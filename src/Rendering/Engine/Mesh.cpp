#include "Mesh.h"
#include <utility>

namespace Rendering::Engine {

Mesh::Mesh(std::vector<Geometries::Vertex3D> const& vertices)
{
    generateVbo(vertices);
    generateVao();
}

void Mesh::generateVbo(std::vector<Geometries::Vertex3D> const& vertices)
{
    glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Geometries::Vertex3D), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::generateVao()
{
    glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Geometries::Vertex3D), reinterpret_cast<void*>(offsetof(Geometries::Vertex3D, _position)));

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Geometries::Vertex3D), reinterpret_cast<void*>(offsetof(Geometries::Vertex3D, _normal)));

    glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);
    glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Geometries::Vertex3D), reinterpret_cast<void*>(offsetof(Geometries::Vertex3D, _texture)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) noexcept
    : _vbo(std::exchange(other._vbo, 0)), _vao(std::exchange(other._vao, 0))
{}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other)
    {
        // Clean up existing resources
        glDeleteBuffers(1, &_vbo);
        glDeleteVertexArrays(1, &_vao);

        // Move resources from other
        _vbo = std::exchange(other._vbo, 0);
        _vao = std::exchange(other._vao, 0);
    }
    return *this;
}

Mesh::~Mesh()
{
    // Clean up existing resources
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
}

void Mesh::draw(GLsizei verticesSize) const
{
    glBindVertexArray(_vao);
    glDrawArrays(GL_TRIANGLES, 0, verticesSize);
    glBindVertexArray(0);
}

} // namespace Rendering::Engine