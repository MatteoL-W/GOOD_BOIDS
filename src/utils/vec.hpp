#pragma once

#include <glm/glm.hpp>

namespace utils::vec {

template<typename Vec>
void limit(Vec& vector, float max)
{
    if (glm::length(vector) > max)
        vector = glm::normalize(vector) * max;
}

} // namespace utils::vec
