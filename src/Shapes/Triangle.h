#pragma once

#include <p6/p6.h>

namespace Shapes {

class Triangle {
public:
    explicit Triangle(glm::vec2 const& position, float const& radius);
    void update(p6::Context& ctx, const std::vector<Shapes::Triangle>& _triangles);
    void draw(p6::Context& ctx);

private:
    [[nodiscard]] std::vector<Triangle> getNearbyTriangles(std::vector<Shapes::Triangle> const&, double radius = 0.1f);
    [[nodiscard]] glm::vec2             computeSeparationForce(const std::vector<Shapes::Triangle>& _triangles);
    void                                keepTriangleInTheScreen(const p6::Context& ctx);

private:
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};

    float _maxSpeed = 2.f;
    float _radius;
};

} // namespace Shapes
