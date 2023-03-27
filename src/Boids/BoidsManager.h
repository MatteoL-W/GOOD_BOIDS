#pragma once

#include <p6/p6.h>
#include <variant>
#include "Boid.h"
#include "Boids/Configs.h"
#include "Food/FoodProvider.h"
#include "Obstacles/ObstaclesManager.h"
#include "Shapes/2D.h"

struct Species {
    ShapesType     _shape;
    int            _quantity;
    BehaviorConfig _behaviorConfig;
    ForcesConfig   _forcesConfig;
};

class BoidsManager {
public:
    BoidsManager() = default;
    void addSpecies(p6::Context&, Species&);

    void update(ObstaclesManager const&, FoodProvider&);
    void draw(p6::Context&);

    void updateForcesConfig(ForcesConfig const&);
    void updateBehaviorConfig(BehaviorConfig const&);
    void reset() { _boids.clear(); };

private:
    inline static unsigned int _speciesCounter = 0;
    std::vector<Boid>          _boids{};
};
