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

BoidsShapesType const& getCloudInstance()
{
    static BoidsShapesType const cloud = Cloud{};
    return cloud;
}

SpectatorShapesType const& getSpectatorShapeInstance()
{
    static SpectatorShapesType const cone = Duck{};
    return cone;
}

ObstaclesShapesType const& getObstacleShapeInstance() {
    static ObstaclesShapesType const sphere = Sphere{0.5};
    return sphere;
}

} // namespace Rendering::Shapes