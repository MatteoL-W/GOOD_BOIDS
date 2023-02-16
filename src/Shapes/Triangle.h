#pragma once

#include <p6/p6.h>

namespace Shapes {

class Triangle {
public:
    explicit Triangle(glm::vec2 const& position, p6::Angle const& direction, float const& radius, float const& speed = 0.01f);
    void update(p6::Context& ctx);
    void draw(p6::Context& ctx);
    void drawInRed(p6::Context& ctx);

    [[nodiscard]] glm::vec2 getPosition() const { return _position; };
    [[nodiscard]] p6::Angle getDirection() const { return _direction; };

private:
    [[nodiscard]] std::vector<Triangle> getNearbyTriangles(const std::vector<Shapes::Triangle>&, double radius = 0.2f);

private:
    glm::vec2 _position{};
    p6::Angle _direction{};
    float     _radius;
    float     _speed;
};

} // namespace Shapes
