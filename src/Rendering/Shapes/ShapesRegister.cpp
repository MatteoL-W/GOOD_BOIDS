#include "ShapesRegister.h"
#include "Rendering/Shapes/ShapesRegister.h"

namespace Rendering::Shapes {

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

ShapesType const& getDuckInstance()
{
    static ShapesType const cone = Duck{};
    return cone;
}

// ShapesType const& getPlaneInstance(float radius)
// {
//     static ShapesType const plane = Plane{radius};
//     return plane;
// }

} // namespace Rendering::Shapes