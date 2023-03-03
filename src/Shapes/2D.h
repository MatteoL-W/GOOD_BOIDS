#pragma once

#include <p6/p6.h>
#include "SingleBoid.h"

namespace Shapes::TwoDimensions {

struct Triangle {
    Triangle() = default;
    explicit Triangle(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()},
            p6::Rotation{p6::Angle{boid.getVelocity()}}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

struct Circle {
    Circle() = default;
    explicit Circle(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill = {1, 1, 1, 1};
        ctx.circle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

struct Fish {
    Fish() = default;
    explicit Fish(float radius)
        : _radius(radius){};

    static void draw(p6::Context& ctx, SingleBoid boid)
    {
        ctx.fill   = {1, 1, 1, 1};
        ctx.stroke = {1, 1, 1, 1};
        ctx.equilateral_triangle(
            // Position in the inverse direction multiplied to be approximately 80% of the circle
            p6::Center{boid.getPosition() - 2.f * glm::vec2(boid.getRadius() * 80) * boid.getVelocity()},
            p6::Radius{static_cast<float>(boid.getRadius())},
            p6::Rotation{p6::Angle{boid.getVelocity()}}
        );
        ctx.circle(
            p6::Center{boid.getPosition()},
            p6::Radius{boid.getRadius()}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::TwoDimensions
