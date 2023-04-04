#pragma once

#include <p6/p6.h>
#include <variant>
#include "Boid.h"
#include "Boids/Configs.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "Shapes/3D.h"

struct Species {
    // ToDo: Can do better ? We do that to increment the _id
    Species(ShapesType shape, int quantity, BehaviorConfig behaviorConfig, ForcesConfig forcesConfig)
        : _id(_speciesCounter++), _shape(shape), _quantity(quantity), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
    {}

    unsigned int   _id;
    ShapesType     _shape;
    int            _quantity;
    BehaviorConfig _behaviorConfig;
    ForcesConfig   _forcesConfig;

    inline static unsigned int _speciesCounter = 0;
};

class BoidsManager {
public:
    BoidsManager() = default;
    void addSpecies(p6::Context&, Species&);

    void update(Features::ObstaclesManager const&, Features::FoodProvider&);
    void draw(p6::Context&);

    void updateForcesConfig(unsigned int speciesId, ForcesConfig const&);
    void updateBehaviorConfig(unsigned int speciesId, BehaviorConfig const&);
    void reset() { _boids.clear(); };

private:
    std::vector<Boid> _boids{};
};
