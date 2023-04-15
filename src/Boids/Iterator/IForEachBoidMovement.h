#pragma once

#include "Boids/Movement.h"

namespace Boids {

class Movement;

namespace Iterator {

class IForEachBoidMovement {
public:
    virtual void loop(std::function<void(const Movement&)>) const = 0;
};

} // namespace Iterator

} // namespace Boids