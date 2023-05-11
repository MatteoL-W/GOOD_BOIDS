#include "ShapesRegister.h"

namespace Rendering::Shapes {

BoidsShapesType const& getSphereInstance(float radius)
{
    static BoidsShapesType const sphere = Sphere{radius};
    return sphere;
}

BoidsShapesType const& getDuckInstance()
{
    static BoidsShapesType const cone = Duck{};
    return cone;
}

SpectatorShapesType const& getDuckInstance2()
{
    static SpectatorShapesType const cone = Duck{};
    return cone;
}

} // namespace Rendering::Shapes