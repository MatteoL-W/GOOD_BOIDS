#pragma once

#include <glm/glm.hpp>

namespace Rendering::Geometries {

struct Vertex3D {
    glm::vec3 _position;
    glm::vec3 _normal;
    glm::vec2 _texture;
};

} // namespace Rendering::Geometries
