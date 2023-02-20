#pragma once

#include <p6/p6.h>
#include "SingleBoid.h"

namespace Shapes::TwoDimensions {
struct Triangle {
    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()},
            p6::Rotation{p6::Angle{boid.getVelocity()}}
        );
    }
};
} // namespace Shapes::TwoDimensions
