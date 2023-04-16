#include "geometriesVertices.hpp"
#include <cmath>
#include <vector>
#include "glpp-extended/lib/glm/glm/glm.hpp"
#include "glpp-extended/lib/glm/glm/gtc/constants.hpp"

namespace Rendering::Geometries {

std::vector<Rendering::Geometries::Vertex3D> sphere_vertices(float radius, size_t discLat, size_t discLong) // NOLINT(bugprone-easily-swappable-parameters, readability-inconsistent-declaration-parameter-name)
{
    // ToDo: Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs

    const auto fDiscLat  = static_cast<float>(discLat);
    const auto fDiscLong = static_cast<float>(discLong);

    const float phi   = 2.f * glm::pi<float>() / fDiscLat;
    const float theta = glm::pi<float>() / fDiscLong;

    std::vector<Rendering::Geometries::Vertex3D> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discLong; ++j)
    {
        const auto fj = static_cast<float>(j);

        const float cosTheta = std::cos(-glm::pi<float>() / 2.f + fj * theta);
        const float sinTheta = std::sin(-glm::pi<float>() / 2.f + fj * theta);

        for (size_t i = 0; i <= discLat; ++i)
        {
            const auto                      fi = static_cast<float>(i);
            Rendering::Geometries::Vertex3D vertex{};

            vertex._texture.x = fi / fDiscLat;
            vertex._texture.y = 1.f - fj / fDiscLong;

            vertex._normal.x = std::sin(fi * phi) * cosTheta;
            vertex._normal.y = sinTheta;
            vertex._normal.z = std::cos(fi * phi) * cosTheta;

            vertex._position = radius * vertex._normal;

            data.push_back(vertex);
        }
    }

    std::vector<Rendering::Geometries::Vertex3D> vertices{};
    for (size_t j = 0; j < discLong; ++j)
    {
        const size_t offset = j * (discLat + 1);
        for (size_t i = 0; i < discLat; ++i)
        {
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + (i + 1)]);
            vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + discLat + 1 + (i + 1)]);
            vertices.push_back(data[offset + i + discLat + 1]);
        }
    }

    return vertices;
}

std::vector<Rendering::Geometries::Vertex3D> cone_vertices(float height, float radius, size_t discLat, size_t discHeight)
{
    // ToDo: Attention ! dans cette implantation on duplique beaucoup de sommets. Une meilleur stratégie est de passer
    // par un Index Buffer Object, que nous verrons dans les prochains TDs

    const auto fDiscLat    = static_cast<float>(discLat);
    const auto fDiscHeight = static_cast<float>(discHeight);

    const float phi = 2.f * glm::pi<float>() / fDiscLat;
    const float h   = height / fDiscHeight;

    std::vector<Rendering::Geometries::Vertex3D> data;

    // Construit l'ensemble des vertex
    for (size_t j = 0; j <= discHeight; ++j)
    {
        for (size_t i = 0; i < discLat; ++i)
        {
            const auto fj = static_cast<float>(j);
            const auto fi = static_cast<float>(i);

            Rendering::Geometries::Vertex3D vertex{};

            vertex._texture.x = fi / fDiscLat;
            vertex._texture.y = fj / fDiscHeight;

            vertex._position.x = radius * (height - fj * h) * std::sin(fi * phi) / height;
            vertex._position.y = fj * h;
            vertex._position.z = radius * (height - fj * h) * std::cos(fi * phi) / height;

            vertex._normal.x = std::sin(fi * phi);
            vertex._normal.y = radius / height;
            vertex._normal.z = std::cos(fi * phi);
            vertex._normal   = glm::normalize(vertex._normal);

            data.push_back(vertex);
        }
    }

    std::vector<Rendering::Geometries::Vertex3D> vertices{};
    for (size_t j = 0; j < discHeight; ++j)
    {
        const size_t offset = j * discLat;
        for (size_t i = 0; i < discLat; ++i)
        {
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + (i + 1) % discLat]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i]);
            vertices.push_back(data[offset + discLat + (i + 1) % discLat]);
            vertices.push_back(data[offset + i + discLat]);
        }
    }

    return vertices;
}

} // namespace Rendering::Geometries