#pragma once

#include <p6/p6.h>

namespace utils {

struct TransformAttributes {
    glm::vec3 _position{};
    glm::vec3 _velocity{};
    glm::vec3 _left{};

    // Where we add our forces
    glm::vec3 _acceleration{};
};

} // namespace utils
