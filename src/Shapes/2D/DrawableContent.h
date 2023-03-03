#pragma once

#include <p6/p6.h>

namespace Shapes::TwoDimensions {
    struct DrawableContent {
        glm::vec2 _position;
        glm::vec2 _velocity;
        float _radius;
    };
}
