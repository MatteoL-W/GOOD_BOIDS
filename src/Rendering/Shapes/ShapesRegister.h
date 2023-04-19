#pragma once

#include "Rendering/Shapes/List/Cone.h"
#include "Rendering/Shapes/List/Duck.h"
#include "Rendering/Shapes/List/Sphere.h"

#include "Rendering/Shapes/List/Plane.h"

using ShapesType = std::variant<Rendering::Shapes::Sphere, Rendering::Shapes::Cone, Rendering::Shapes::Duck>;

namespace Rendering::Shapes {

ShapesType const& getSphereInstance(float radius);
ShapesType const& getConeInstance(float radius);
ShapesType const& getDuckInstance();

} // namespace Rendering::Shapes
