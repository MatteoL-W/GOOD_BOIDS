#pragma once

#include "Rendering/Shapes/List/Cloud.h"
#include "Rendering/Shapes/List/Drop.h"
#include "Rendering/Shapes/List/Sheep.h"
#include "Rendering/Shapes/List/Sphere.h"

using BoidsShapesType     = std::variant<Rendering::Shapes::Cloud>;
using SpectatorShapesType = std::variant<Rendering::Shapes::Sheep>;
using ObstaclesShapesType = std::variant<Rendering::Shapes::Drop>;
using FoodShapesType      = std::variant<Rendering::Shapes::Sphere>;

namespace Rendering::Shapes {

BoidsShapesType const&     getCloudInstance();
SpectatorShapesType const& getSpectatorShapeInstance();
ObstaclesShapesType const& getDropShapeInstance();
FoodShapesType const&      getFoodShapeInstance(float radius);

} // namespace Rendering::Shapes
