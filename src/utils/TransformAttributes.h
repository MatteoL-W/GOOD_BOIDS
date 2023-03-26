#pragma once

#include <p6/p6.h>

namespace Utils {

struct TransformAttributes {
    glm::vec2 _position{};
    glm::vec2 _velocity{};

    // Where we add our forces
    glm::vec2 _acceleration{};
};

} // namespace utils
