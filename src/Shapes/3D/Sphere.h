#pragma once

#include <p6/p6.h>
#include "utils/TransformAttributes.h"

namespace Shapes::ThreeDimensions {

class Sphere {
public:
    Sphere() = default;

    explicit Sphere(float radius)
        : _radius(radius){};

    void draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes) const
    {
        ctx.circle(
            p6::Center{transformAttributes._position},
            p6::Radius{_radius}
        );
    }

    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float _radius;
};

} // namespace Shapes::ThreeDimensions
