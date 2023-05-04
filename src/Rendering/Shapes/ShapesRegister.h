#pragma once

#include "Rendering/Shapes/List/Cone.h"
#include "Rendering/Shapes/List/Duck.h"
#include "Rendering/Shapes/List/Plane.h"
#include "Rendering/Shapes/List/Sphere.h"
#include "Rendering/Shapes/List/Cube.h"

using ShapesType = std::variant<Rendering::Shapes::Sphere, Rendering::Shapes::Cone, Rendering::Shapes::Duck, Rendering::Shapes::Plane, Rendering::Shapes::Cube>;

namespace Rendering::Shapes {

ShapesType const& getSphereInstance(float radius);
ShapesType const& getConeInstance(float radius);
ShapesType const& getDuckInstance();
ShapesType const& getPlaneInstance(float radius, std::vector<Rendering::Geometries::Vertex3D> vertices);

} // namespace Rendering::Shapes
