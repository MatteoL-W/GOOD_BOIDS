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
        ctx.fill = {1, 1, 1, 1};
        ctx.circle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()}
        );
        ctx.equilateral_triangle(
            p6::Center{boid.getPosition() - glm::vec2(1.5)*(boid.getVelocity() * glm::vec2(0.01)) },
            p6::Radius{static_cast<float>(boid.getRadius())},
            p6::Rotation{p6::Angle{boid.getVelocity()}}
        );
    }
};

} // namespace Shapes::TwoDimensions
