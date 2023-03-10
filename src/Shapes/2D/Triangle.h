#pragma once

#include <p6/p6.h>
#include "Boids/SingleBoid.h"

namespace Shapes::TwoDimensions {

class Triangle {
public:
    Triangle() = default;

    explicit Triangle(float radius)
        : _radius(radius){};

    void draw(p6::Context& ctx, TransformAttributes const& transformAttributes) const
    {
        ctx.equilateral_triangle(
            p6::Center{transformAttributes._position},
            p6::Radius{_radius},
            p6::Rotation{p6::Angle{transformAttributes._velocity}}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::TwoDimensions
