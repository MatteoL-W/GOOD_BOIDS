#pragma once

namespace Boids {

struct Species {

    // In order to have the species initiated as member in the scene
    explicit Species(BoidsShapesType const& shape) : _shape(shape) {}

    unsigned int           _id{_speciesCounter++};
    BoidsShapesType const& _shape;
    int                    _quantity{};
    BehaviorConfig         _behaviorConfig{};
    ForcesConfig           _forcesConfig{};

    inline static unsigned int _speciesCounter = 0;
};

} // namespace Boids