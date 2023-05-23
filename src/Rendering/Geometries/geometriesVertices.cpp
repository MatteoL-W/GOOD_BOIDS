#include "geometriesVertices.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>

namespace Rendering::Geometries {

std::vector<Vertex3D> generateSphereVertices(float radius, size_t discretizationLatitude, size_t discretizationLongitude) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    const auto fDiscLat  = static_cast<float>(discretizationLatitude);
    const auto fDiscLong = static_cast<float>(discretizationLongitude);

    const float phi   = 2.f * glm::pi<float>() / fDiscLat;
    const float theta = glm::pi<float>() / fDiscLong;

    std::vector<Vertex3D> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discretizationLongitude; ++j)
    {
        const auto fj = static_cast<float>(j);

        const float cosTheta = std::cos(-glm::pi<float>() / 2.f + fj * theta);
        const float sinTheta = std::sin(-glm::pi<float>() / 2.f + fj * theta);

        for (size_t i = 0; i <= discretizationLatitude; ++i)
        {
            const auto fi = static_cast<float>(i);
            Vertex3D   vertex{};

            vertex._texture.x = fi / fDiscLat;
            vertex._texture.y = 1.f - fj / fDiscLong;

            vertex._normal.x = std::sin(fi * phi) * cosTheta;
            vertex._normal.y = sinTheta;
            vertex._normal.z = std::cos(fi * phi) * cosTheta;

            vertex._position = radius * vertex._normal;

            data.push_back(vertex);
        }
    }

    std::vector<Vertex3D> vertices{};
    for (size_t j = 0; j < discretizationLongitude; ++j)
    {
        const size_t offset = j * (discretizationLatitude + 1);
        for (size_t i = 0; i < discretizationLatitude; ++i)
        {
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + (i + 1)]);
            vertices.push_back(data[offset + discretizationLatitude + 1 + (i + 1)]);
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + discretizationLatitude + 1 + (i + 1)]);
            vertices.push_back(data[offset + i + discretizationLatitude + 1]);
        }
    }

    return vertices;
}

std::vector<Vertex3D> generatePlaneVertices()
{
    return std::vector<Vertex3D>{{{-1.f, 0.0f, -1.f}, {0.0f, 1.f, 0.0f}, {0.0f, 0.0f}}, {{1.f, 0.0f, -1.f}, {0.0f, 1.f, 0.0f}, {1.f, 0.0f}}, {{1.f, 0.0f, 1.f}, {0.0f, 1.f, 0.0f}, {1.f, 1.f}}, {{-1.f, 0.0f, -1.f}, {0.0f, 1.f, 0.0f}, {0.0f, 0.0f}}, {{1.f, 0.0f, 1.f}, {0.0f, 1.f, 0.0f}, {1.f, 1.f}}, {{-1.f, 0.0f, 1.f}, {0.0f, 1.f, 0.0f}, {0.0f, 1.f}}};
}

// Function to create and return the skybox vertices
std::array<float, 108> generateSkyboxVertices()
{
    static constexpr float radius = 10.f;
    return {
        -radius, radius, -radius,
        -radius, -radius, -radius,
        radius, -radius, -radius,
        radius, -radius, -radius,
        radius, radius, -radius,
        -radius, radius, -radius,

        -radius, -radius, radius,
        -radius, -radius, -radius,
        -radius, radius, -radius,
        -radius, radius, -radius,
        -radius, radius, radius,
        -radius, -radius, radius,

        radius, -radius, -radius,
        radius, -radius, radius,
        radius, radius, radius,
        radius, radius, radius,
        radius, radius, -radius,
        radius, -radius, -radius,

        -radius, -radius, radius,
        -radius, radius, radius,
        radius, radius, radius,
        radius, radius, radius,
        radius, -radius, radius,
        -radius, -radius, radius,

        -radius, radius, -radius,
        radius, radius, -radius,
        radius, radius, radius,
        radius, radius, radius,
        -radius, radius, radius,
        -radius, radius, -radius,

        -radius, -radius, -radius,
        -radius, -radius, radius,
        radius, -radius, -radius,
        radius, -radius, -radius,
        -radius, -radius, radius,
        radius, -radius, radius};
}

} // namespace Rendering::Geometries
