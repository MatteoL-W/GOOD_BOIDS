#pragma once

#include <p6/p6.h>

namespace Shapes {

class Triangle {
public:
    explicit Triangle(glm::vec2 const& position, float const& radius, float const& speed = 0.01f);
    void update(p6::Context& ctx, const std::vector<Shapes::Triangle>& _triangles);
    void draw(p6::Context& ctx);

    [[nodiscard]] glm::vec2 getPosition() const { return _position; };

private:
    [[nodiscard]] std::vector<Triangle> getNearbyTriangles(std::vector<Shapes::Triangle> const&, double radius = 0.2f);
    [[nodiscard]] glm::vec2             computeSeparationForce(const std::vector<Shapes::Triangle>& _triangles);

private:
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};
    float     _radius;
    float     _speed;
};

} // namespace Shapes
