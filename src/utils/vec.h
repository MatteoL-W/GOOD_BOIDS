#pragma once

#include <glm/glm.hpp>

namespace utils::vec {

/// Constrain the vector speed between a min and a max.
template<typename Vec>
void constrain(Vec& vector, float min, float max)
{
    float current_speed = glm::length(vector);

    if (current_speed < min)
        vector = glm::normalize(vector) * min;
    else if (current_speed > max)
        vector = glm::normalize(vector) * max;
}

} // namespace utils::vec
