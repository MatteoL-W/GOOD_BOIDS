#pragma once

#include <p6/p6.h>
#include "DrawableContent.h"

namespace Shapes::TwoDimensions {

class Triangle {
public:
    Triangle() = default;

    explicit Triangle(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, DrawableContent const& content)
    {
        ctx.fill = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            p6::Center{content._position},
            p6::Radius{content._radius},
            p6::Rotation{p6::Angle{content._velocity}}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::TwoDimensions
