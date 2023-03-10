#pragma once

#include "2D/Circle.h"
#include "2D/Fish.h"
#include "2D/Triangle.h"

using ShapesType = std::variant<
    Shapes::TwoDimensions::Triangle,
    Shapes::TwoDimensions::Circle,
    Shapes::TwoDimensions::Fish>;
