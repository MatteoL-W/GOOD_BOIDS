#pragma once

#include <p6/p6.h>
#include "Rendering/Geometries/Vertex3D.hpp"

namespace Rendering::Engine {

class Mesh {
public:
    explicit Mesh(std::vector<Geometries::Vertex3D> const&);
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    ~Mesh();

    void draw(GLsizei verticesSize) const;

private:
    void generateVbo(std::vector<Geometries::Vertex3D> const& vertices);
    void generateVao();

private:
    static const GLuint VERTEX_ATTR_POSITION   = 0;
    static const GLuint VERTEX_ATTR_NORMAL     = 1;
    static const GLuint VERTEX_ATTR_TEX_COORDS = 2;

    GLuint _vbo = 0;
    GLuint _vao = 0;
};

} // namespace Rendering::Engine
