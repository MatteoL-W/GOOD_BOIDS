#pragma once

#include "3D/Sphere.h"
#include "3D/Cone.h"

using ShapesType = std::variant<Shapes::ThreeDimensions::Sphere, Shapes::ThreeDimensions::Cone>;

namespace Shapes::ThreeDimensions {

ShapesType const& getSphereInstance(float radius);
ShapesType const& getConeInstance(float radius);

} // namespace Shapes::ThreeDimensions
