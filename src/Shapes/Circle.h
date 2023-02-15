#pragma once

#include <p6/p6.h>

namespace Shapes {

class Circle {
public:
    explicit Circle(glm::vec2 const& position, p6::Angle const& direction, float const& radius);
    void update(p6::Context& ctx);
    void draw(p6::Context& ctx);

private:
    glm::vec2 _position{};
    p6::Angle _direction{}; // Angle should be between 0 and TAU
    float     _radius;
};

} // namespace Shapes
