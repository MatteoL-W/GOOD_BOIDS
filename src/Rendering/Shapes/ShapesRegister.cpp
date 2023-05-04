#include "ShapesRegister.h"

#include <utility>
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

ShapesType const& getPlaneInstance(float radius, std::vector<Rendering::Geometries::Vertex3D> vertices)
{
    static ShapesType const plane = Plane{radius, std::move(vertices)};
    return plane;
}

} // namespace Rendering::Shapes