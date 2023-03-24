#pragma once

#include <p6/p6.h>
#include <variant>
#include "Food/FoodProvider.h"
#include "Obstacles/Obstacles.h"
#include "Shapes/2D.h"
#include "SingleBoid.h"

struct Species {
    ShapesType     _shape;
    int            _quantity;
    BehaviorConfig _behaviorConfig;
    ForcesConfig   _forcesConfig;
};

class Boids {
public:
    Boids() = default;

    void addSpecies(p6::Context&, Species&);

    void updateAndDraw(p6::Context&, Obstacles const&, FoodProvider&);
    void updateForcesConfig(ForcesConfig const&);
    void updateBehaviorConfig(BehaviorConfig const&);
    void reset() { _boids.clear(); };
    // void updateShape(ShapesType const& shape) { _shape = shape; };
    // void updateRadius(float radius);

private:
    inline static unsigned int _speciesNumber = 0;
    std::vector<SingleBoid>    _boids{};
    // ShapesType              _shape{};
};
