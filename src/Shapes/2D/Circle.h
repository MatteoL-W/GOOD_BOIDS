#pragma once

#include <p6/p6.h>
#include "SingleBoid.h"

namespace Shapes::TwoDimensions {

class Circle {
public:
    Circle() = default;

    explicit Circle(float radius)
        : _radius(radius){};

    void draw(p6::Context& ctx, Movement const& movement) const
    {
        ctx.fill = {1, 1, 1, 1};
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
