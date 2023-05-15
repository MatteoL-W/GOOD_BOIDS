#pragma once

#include "Rendering/Shapes/List/Cloud.h"
#include "Rendering/Shapes/List/Duck.h"
#include "Rendering/Shapes/List/Sphere.h"

using BoidsShapesType     = std::variant<Rendering::Shapes::Sphere, Rendering::Shapes::Duck, Rendering::Shapes::Cloud>;
using SpectatorShapesType = std::variant<Rendering::Shapes::Duck>;
using ObstaclesShapesType = std::variant<Rendering::Shapes::Sphere>;

namespace Rendering::Shapes {

BoidsShapesType const& getSphereInstance(float radius);
BoidsShapesType const& getConeInstance(float radius);
BoidsShapesType const& getDuckInstance();
BoidsShapesType const& getCloudInstance();

SpectatorShapesType const& getSpectatorShapeInstance();

ObstaclesShapesType const& getObstacleShapeInstance();

} // namespace Rendering::Shapes
