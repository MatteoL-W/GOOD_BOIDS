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

struct Circle {
    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill = {1, 1, 1, 1};
        ctx.circle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()}
        );
    }
};

struct Fish {
    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill   = {1, 1, 1, 1};
        ctx.stroke = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            // Position in the inverse direction multiplied to be approximately 80% of the circle
            p6::Center{boid.getPosition() - glm::vec2(boid.getRadius() * 80) * boid.getVelocity()},
            p6::Radius{static_cast<float>(boid.getRadius())},
            p6::Rotation{p6::Angle{boid.getVelocity()}}
        );
        ctx.circle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()}
        );
    }
};

} // namespace Shapes::TwoDimensions
