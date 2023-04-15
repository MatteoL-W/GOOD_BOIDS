#pragma once

#include "Rendering/Shapes/2D/Circle.h"
#include "Rendering/Shapes/2D/Fish.h"
#include "Rendering/Shapes/2D/Triangle.h"

using ShapesType = std::variant<
    Shapes::TwoDimensions::Triangle,
    Shapes::TwoDimensions::Circle,
    Shapes::TwoDimensions::Fish>;
