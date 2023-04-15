#pragma once

#include "Rendering/Shapes/3D/Cone.h"
#include "Rendering/Shapes/3D/Duck.h"
#include "Rendering/Shapes/3D/Sphere.h"

using ShapesType = std::variant<Shapes::ThreeDimensions::Sphere, Shapes::ThreeDimensions::Cone, Shapes::ThreeDimensions::Duck>;

namespace Shapes::ThreeDimensions {

ShapesType const& getSphereInstance(float radius);
ShapesType const& getConeInstance(float radius);
ShapesType const& getDuckInstance();

} // namespace Shapes::ThreeDimensions
