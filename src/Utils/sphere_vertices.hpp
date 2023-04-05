#pragma once

#include <vector>
#include "Vertex3D.hpp"

namespace glimac {

std::vector<Utils::Vertex3D> sphere_vertices(float radius, size_t discretization_latitude, size_t discretization_longitude);

} // namespace glimac