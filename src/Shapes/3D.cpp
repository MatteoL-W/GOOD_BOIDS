#include "3D.h"

namespace Shapes::ThreeDimensions {

ShapesType const& get_sphere_instance()
{
    static ShapesType const sphere = Sphere{0.1f};
    return sphere;
}

} // namespace Shapes::ThreeDimensions