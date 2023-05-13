#pragma once

namespace Boids {

struct Species {
    unsigned int           _id{_speciesCounter++};
    BoidsShapesType const& _shape;
    int                    _quantity{};
    BehaviorConfig         _behaviorConfig{};
    ForcesConfig           _forcesConfig{};

    inline static unsigned int _speciesCounter = 0;
};

} // namespace Boids