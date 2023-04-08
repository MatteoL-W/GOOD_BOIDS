#pragma once

#include "Boids/BoidMovement.h"
#include "IForEachBoidMovement.h"

template<typename T>
class ForEachBoidMovement : public IForEachBoidMovement {
public:
    explicit ForEachBoidMovement(std::vector<T> const& boids)
        : _boids(boids){};

    void loop(std::function<void(const BoidMovement&)> boidUpdate) const override
    {
        for (auto const& boid : _boids)
            boidUpdate(boid.getMovement());
    }

private:
    std::vector<T> _boids;
};
