#pragma once

#include "Boids/BoidMovement.h"

class BoidMovement;

class IForEachBoidMovement {
public:
    virtual void loop(std::function<void(const BoidMovement&)>) const = 0;
};