#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include "Program/Normal.h"
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
        glBufferData(GL_ARRAY_BUFFER, __vertices.size() * sizeof(Utils::Vertex3D), __vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /** VAO **/
        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        const GLuint VERTEX_ATTR_POSITION   = 10;
        const GLuint VERTEX_ATTR_NORMAL     = 11;
        const GLuint VERTEX_ATTR_TEX_COORDS = 12;

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);

        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), reinterpret_cast<void*>(offsetof(Utils::Vertex3D, _position)));

        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), reinterpret_cast<void*>(offsetof(Utils::Vertex3D, _normal)));

        glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);
        glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), reinterpret_cast<void*>(offsetof(Utils::Vertex3D, _texture)));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        /** FIN VBO **/

        glBindVertexArray(0);
        /** FIN VAO **/
    };

    Sphere(Sphere&& other)
        : _radius(other._radius), _vbo(std::exchange(other._vbo, 0)), _vao(std::exchange(other._vao, 0))
    {}

    Sphere& operator=(Sphere&& other)
    {
        if (this != &other) {
            // Clean up existing resources
            glDeleteBuffers(1, &_vbo);
            glDeleteVertexArrays(1, &_vao);

            // Move resources from other
            _radius = other._radius;
            _vbo = std::exchange(other._vbo, 0);
            _vao = std::exchange(other._vao, 0);
        }
        return *this;
    }

    ~Sphere()
    {
        glDeleteBuffers(1, &_vbo); // 1 car 1 seul vbo
        glDeleteVertexArrays(1, &_vao);
    }

    Sphere(const Sphere& other)                = delete;
    Sphere& operator=(const Sphere& other)     = delete;

    void draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes) const
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

        glBindVertexArray(_vao);
        glDrawArrays(GL_TRIANGLES, 0, __vertices.size());
        glBindVertexArray(0);
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                                            _radius{};
    GLuint                                           _vbo = 0;
    GLuint                                           _vao = 0;
    Program::Normal                                  _shader{};
    static inline const std::vector<Utils::Vertex3D> __vertices{glimac::sphere_vertices(1.f, 32, 16)};
};

} // namespace Shapes::ThreeDimensions