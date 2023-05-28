#include "ShapesRegister.h"

namespace Rendering::Shapes {

BoidsShapesType const& getCloudInstance()
{
    static BoidsShapesType const cloud = Cloud{};
    return cloud;
}

BoidsShapesType const& getBlueCloudInstance()
{
    static BoidsShapesType const cloud = BlueCloud{};
    return cloud;
}

BoidsShapesType const& getPinkCloudInstance()
{
    static BoidsShapesType const cloud = PinkCloud{};
    return cloud;
}

SpectatorShapesType const& getSpectatorShapeInstance()
{
    static SpectatorShapesType const cone = Sheep{};
    return cone;
}

ObstaclesShapesType const& getDropShapeInstance() {
    static ObstaclesShapesType const shape = Drop{};
    return shape;
}

FoodShapesType const& getFoodShapeInstance(float radius) {
    static FoodShapesType const star = Star{radius};
    return star;
}

} // namespace Rendering::Shapes