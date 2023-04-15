#pragma once

#include "3D/Sphere.h"
#include "3D/Cone.h"
#include "3D/Duck.h"

using ShapesType = std::variant<Shapes::ThreeDimensions::Sphere, Shapes::ThreeDimensions::Cone, Shapes::ThreeDimensions::Duck>;

namespace Shapes::ThreeDimensions {

ShapesType const& getSphereInstance(float radius);
ShapesType const& getConeInstance(float radius);
ShapesType const& getDuckInstance();

} // namespace Shapes::ThreeDimensions
