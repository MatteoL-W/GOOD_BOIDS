#pragma once

#include <p6/p6.h>

namespace Shapes {

class Triangle {
public:
    explicit Triangle(glm::vec2 const& position, p6::Angle const& direction, float const& radius, float const& speed = 0.01f);
    void update(p6::Context& ctx, std::vector<Shapes::Triangle> _triangles);
    void draw(p6::Context& ctx);

    [[nodiscard]] glm::vec2 getPosition() const { return _position; };
    [[nodiscard]] p6::Angle getDirection() const { return _direction; };

private:
    [[nodiscard]] std::vector<Triangle> getNearbyTriangles(std::vector<Shapes::Triangle> const&, double radius = 0.2f);
    [[nodiscard]] glm::vec2             computeSeparationForce(std::vector<Shapes::Triangle> _triangles);
    [[nodiscard]] void             avoidOthersMembers(std::vector<Shapes::Triangle> _triangles);

private:
    glm::vec2 _position{};
    p6::Angle _direction{};
    float     _radius;
    float     _speed;
};

} // namespace Shapes
