#include "ShapesRegister.h"

namespace Rendering::Shapes {

BoidsShapesType const& getSphereInstance(float radius)
{
    static BoidsShapesType const sphere = Sphere{radius};
    return sphere;
}

BoidsShapesType const& getConeInstance(float radius)
{
    static BoidsShapesType const cone = Cone{radius};
    return cone;
}

BoidsShapesType const& getDuckInstance()
{
    static BoidsShapesType const cone = Duck{};
    return cone;
}

} // namespace Rendering::Shapes