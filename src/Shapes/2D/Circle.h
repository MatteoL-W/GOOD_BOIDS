#pragma once

#include <p6/p6.h>
#include "DrawableContent.h"

namespace Shapes::TwoDimensions {

class Circle {
public:
    Circle() = default;

    explicit Circle(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, DrawableContent const& content)
    {
        ctx.fill = {1, 1, 1, 1};
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
