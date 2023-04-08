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
        if (_hasInitialized)
            return;

        /** VBO & VAO **/
        glGenBuffers(1, &_VBO); // 1 car un seul vbo

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(Utils::Vertex3D), VERTICES.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /** VAO **/
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        const GLuint VERTEX_ATTR_POSITION   = 10;
        const GLuint VERTEX_ATTR_NORMAL     = 11;
        const GLuint VERTEX_ATTR_TEX_COORDS = 12;

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);

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

        _hasInitialized = true;
    };

    Sphere(const Sphere& other)
        : _radius(other._radius)
    {
        if (_hasInitialized)
            return;

        /** VBO & VAO **/
        glGenBuffers(1, &_VBO); // 1 car un seul vbo

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);
        glBufferData(GL_ARRAY_BUFFER, VERTICES.size() * sizeof(Utils::Vertex3D), VERTICES.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        /** VAO **/
        glGenVertexArrays(1, &_VAO);
        glBindVertexArray(_VAO);

        const GLuint VERTEX_ATTR_POSITION   = 10;
        const GLuint VERTEX_ATTR_NORMAL     = 11;
        const GLuint VERTEX_ATTR_TEX_COORDS = 12;

        // Bind VBO
        glBindBuffer(GL_ARRAY_BUFFER, _VBO);

        // Position (VEC3)
        glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
        glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), (void*)offsetof(Utils::Vertex3D, _position));

        // Normal (VEC3)
        glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
        glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), (void*)offsetof(Utils::Vertex3D, _normal));

        // Tex Coords (VEC2)
        glEnableVertexAttribArray(VERTEX_ATTR_TEX_COORDS);
        glVertexAttribPointer(VERTEX_ATTR_TEX_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Utils::Vertex3D), (void*)offsetof(Utils::Vertex3D, _texture));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        /** FIN VBO **/

        glBindVertexArray(0);

        _hasInitialized = true;
    }

    Sphere& operator=(const Sphere& other)
    {
        if (this != &other)
        {
            // Copy and swap idiom
            Sphere temp(other);
            std::swap(_radius, temp._radius);
        }
        return *this;
    }

    Sphere(Sphere&& other) noexcept
        : _radius(other._radius)
    {}

    // ToDo: This destructor causes heavy lags.
    ~Sphere()
    {
        if (_hasInitialized)
            return;

        glDeleteBuffers(1, &_VBO); // 1 car 1 seul vbo
        glDeleteVertexArrays(1, &_VAO);
    }

    void draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes) const
    {
        if (!_hasInitialized)
            return;

        SHADER._program.use();

        auto modelViewMatrix = glm::translate(glm::mat4{1}, glm::vec3(0.f, 0.f, -5.f));
        modelViewMatrix      = glm::translate(modelViewMatrix, transformAttributes._position);
        modelViewMatrix      = glm::scale(modelViewMatrix, glm::vec3{getRadius()});

        auto projectionMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), .1f, 100.f);
        auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

        glUniformMatrix4fv(SHADER.uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
        glUniformMatrix4fv(SHADER.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
        glUniformMatrix4fv(SHADER.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, VERTICES.size());
        glBindVertexArray(0);
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                                            _radius{};
    static inline bool                               _hasInitialized = false;
    static inline GLuint                             _VBO            = 0;
    static inline GLuint                             _VAO            = 0;
    Program::Normal              SHADER{};
    static inline const std::vector<Utils::Vertex3D> VERTICES{glimac::sphere_vertices(1.f, 32, 16)};
};

//const Sphere& get_shape_instance(){
//    static Sphere sphere = ...;
//    return shape;
//}

} // namespace Shapes::ThreeDimensions