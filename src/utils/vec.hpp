#pragma once

#include <glm/glm.hpp>

namespace utils::vec {

template<typename Vec>
void constrain(Vec& vector, float min, float max)
{
    if (glm::length(vector) > min)
        vector = glm::normalize(vector) * min;

    if (glm::length(vector) > max)
        vector = glm::normalize(vector) * max;
}

} // namespace utils::vec
