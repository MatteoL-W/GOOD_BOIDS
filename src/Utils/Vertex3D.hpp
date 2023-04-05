#pragma once

#include <glm/glm.hpp>

namespace Utils {

struct Vertex3D {
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texture;
};

} // namespace Utils
