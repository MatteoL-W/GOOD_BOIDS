#pragma once

#include <p6/p6.h>
#include "DrawableContent.h"

namespace Shapes::TwoDimensions {

class Fish {
public:
    Fish() = default;

    explicit Fish(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, DrawableContent const& content)
    {
        ctx.fill   = {1, 1, 1, 1};
        ctx.stroke = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            // Position in the inverse direction multiplied to be approximately 80% of the circle
            p6::Center{content._position - 2.f * glm::vec2(content._radius * 80) * content._velocity},
            p6::Radius{static_cast<float>(content._radius)},
            p6::Rotation{p6::Angle{content._velocity}}
        );
        ctx.circle(
            p6::Center{content._position},
            p6::Radius{content._radius}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::TwoDimensions
