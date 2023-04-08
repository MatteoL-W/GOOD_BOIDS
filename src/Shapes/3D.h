#pragma once

#include "3D/Sphere.h"
#include "3D/Cone.h"

using ShapesType = std::variant<Shapes::ThreeDimensions::Sphere, Shapes::ThreeDimensions::Cone>;

namespace Shapes::ThreeDimensions {

ShapesType const& get_sphere_instance(float radius);
ShapesType const& get_cone_instance(float radius);

} // namespace Shapes::ThreeDimensions
