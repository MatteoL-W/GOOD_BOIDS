#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include "Utils/sphere_vertices.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "utils/TransformAttributes.h"

namespace Shapes::ThreeDimensions {

class Sphere {
public:
    Sphere() = default;

    explicit Sphere(float radius)
        : _radius(radius)
    {
        /** VBO & VAO **/
        glGenBuffers(1, &_vbo); // 1 car un seul vbo

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        _vertices = glimac::sphere_vertices(1.f, 32, 16);
        glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Utils::Vertex3D), _vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /** VAO **/
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        const GLuint VERTEX_ATTR_POSITION   = 10;
        const GLuint VERTEX_ATTR_NORMAL     = 11;
        const GLuint VERTEX_ATTR_TEX_COORDS = 12;

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        // Position (VEC3)
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(
            VERTEX_ATTR_POSITION,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Utils::Vertex3D),
            (void*)offsetof(Utils::Vertex3D, _position)
        );

        // Normal (VEC3)
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(
            VERTEX_ATTR_NORMAL,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Utils::Vertex3D),
            (void*)offsetof(Utils::Vertex3D, _normal)
        );

        // Tex Coords (VEC2)
        glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);
        glVertexAttribPointer(
            VERTEX_ATTR_TEX_COORDS,
            2,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Utils::Vertex3D),
            (void*)offsetof(Utils::Vertex3D, _texture)
        );

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        /** FIN VBO **/

        glBindVertexArray(0);
        /** FIN VAO **/
    };

    // ToDo: This destructor causes a crash.
    ~Sphere()
    {
        glDeleteBuffers(1, &_vbo); // 1 car 1 seul vbo
        glDeleteVertexArrays(1, &_vao);
    }

    void draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes, p6::Shader& shader) const
    {
        auto uMVPMatrix    = glGetUniformLocation(shader.id(), "uMVPMatrix");
        auto uMVMatrix     = glGetUniformLocation(shader.id(), "uMVMatrix");
        auto uNormalMatrix = glGetUniformLocation(shader.id(), "uNormalMatrix");

        shader.use();

        auto modelViewMatrix  = glm::translate(glm::mat4{1}, glm::vec3(0.f, 0.f, -5.f));
        auto projectionMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), .1f, 100.f);
        auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, _vertices.size());
        glBindVertexArray(0);

        /*ctx.circle(
            p6::Center{transformAttributes._position},
            p6::Radius{_radius}
        );*/
    }


    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                        _radius{};
    GLuint                       _vbo = 0;
    GLuint                       _vao = 0;
    std::vector<Utils::Vertex3D> _vertices{};
};

} // namespace Shapes::ThreeDimensions