#include "3D.h"

namespace Shapes::ThreeDimensions {

ShapesType const& getSphereInstance(float radius)
{
    static ShapesType const sphere = Sphere{radius};
    return sphere;
}

ShapesType const& getConeInstance(float radius)
{
    static ShapesType const cone = Cone{radius};
    return cone;
}

} // namespace Shapes::ThreeDimensions