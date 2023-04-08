#pragma once

#include "3D/Sphere.h"

using ShapesType = std::variant<Shapes::ThreeDimensions::Sphere>;

namespace Shapes::ThreeDimensions {
ShapesType const& get_sphere_instance();
} // namespace Shapes::ThreeDimensions
