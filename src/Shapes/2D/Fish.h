#pragma once

#include <p6/p6.h>
#include "Boids/SingleBoid.h"

namespace Shapes::TwoDimensions {

class Fish {
public:
    Fish() = default;

    explicit Fish(float radius)
        : _radius(radius){};

    void draw(p6::Context& ctx, Movement const& movement) const
    {
        ctx.equilateral_triangle(
            // Position in the inverse direction multiplied to be approximately 80% of the circle
            p6::Center{movement._position - 2.f * glm::vec2(_radius * 80) * (movement._velocity * 0.01f)}, // ToDo : cracra
            p6::Radius{static_cast<float>(_radius)},
            p6::Rotation{p6::Angle{movement._velocity * 0.01f}} // ToDo: eurk
        );
        ctx.circle(
            p6::Center{movement._position},
            p6::Radius{_radius}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::TwoDimensions
