#pragma once

#include <p6/p6.h>
#include "utils/TransformAttributes.h"

namespace Shapes::TwoDimensions {

class Triangle {
public:
    Triangle() = default;

    explicit Triangle(float radius)
        : _radius(radius){};

    void draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes) const
    {
        ctx.equilateral_triangle(
            p6::Center{transformAttributes._position},
            p6::Radius{_radius},
            p6::Rotation{p6::Angle{transformAttributes._velocity}}
        );
    }

    float _radius;
};

} // namespace Shapes::TwoDimensions
