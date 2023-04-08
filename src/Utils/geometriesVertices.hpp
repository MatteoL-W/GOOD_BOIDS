#pragma once

#include <vector>
#include "Vertex3D.hpp"

namespace glimac {

std::vector<Utils::Vertex3D> sphere_vertices(float radius, size_t discretization_latitude, size_t discretization_longitude);
std::vector<Utils::Vertex3D> cone_vertices(float height, float radius, size_t discLat, size_t discHeight);

} // namespace glimac