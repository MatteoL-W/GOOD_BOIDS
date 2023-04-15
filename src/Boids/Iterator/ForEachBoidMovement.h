#pragma once

#include "Boids/Movement.h"
#include "IForEachBoidMovement.h"

namespace Boids::Iterator {

template<typename T>
class ForEachBoidMovement : public IForEachBoidMovement {
public:
    explicit ForEachBoidMovement(std::vector<T> const& boids)
        : _boids(boids){};

    void loop(std::function<void(const Movement&)> boidUpdate) const override
    {
        for (auto const& boid : _boids)
            boidUpdate(boid.getMovement());
    }

private:
    std::vector<T> _boids;
};

} // namespace Boids::Iterator