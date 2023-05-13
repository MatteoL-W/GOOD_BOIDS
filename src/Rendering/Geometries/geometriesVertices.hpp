#pragma once

#include <array>
#include <vector>
#include "Rendering/Geometries/Vertex3D.hpp"

namespace Rendering::Geometries {

std::vector<Vertex3D>  sphere_vertices(float radius, size_t discretization_latitude, size_t discretization_longitude);
std::vector<Vertex3D>  cone_vertices(float height, float radius, size_t discLat, size_t discHeight);
std::vector<Vertex3D>  plane_vertices();
std::array<float, 108> skyboxVertices();

} // namespace Rendering::Geometries