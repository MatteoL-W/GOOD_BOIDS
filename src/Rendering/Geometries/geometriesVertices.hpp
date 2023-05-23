#pragma once

#include <array>
#include <vector>
#include "Rendering/Geometries/Vertex3D.hpp"

namespace Rendering::Geometries {

std::vector<Vertex3D>  generateSphereVertices(float radius, size_t discretizationLatitude, size_t discretizationLongitude);
std::vector<Vertex3D>  generatePlaneVertices();
std::array<float, 108> generateSkyboxVertices();

} // namespace Rendering::Geometries