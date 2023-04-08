#include "3D.h"

namespace Shapes::ThreeDimensions {

ShapesType const& get_sphere_instance(float radius)
{
    static ShapesType const sphere = Sphere{radius};
    return sphere;
}

ShapesType const& get_cone_instance(float radius)
{
    static ShapesType const cone = Cone{radius};
    return cone;
}

} // namespace Shapes::ThreeDimensions