#pragma once

#include <p6/p6.h>
#include <variant>
#include "Food/FoodProvider.h"
#include "Obstacles/Obstacles.h"
#include "Shapes/2D.h"
#include "SingleBoid.h"

class Boids {
public:
    Boids() = default;

    void addSpecies(p6::Context&, unsigned int quantity, ShapesType const&, BehaviorConfig const&, ForcesConfig const&);

    void updateAndDraw(p6::Context&, Obstacles const&, FoodProvider&);
    void updateForcesConfig(ForcesConfig const&);
    void updateBehaviorConfig(BehaviorConfig const&);
    void reset() { _boids.clear(); };
    //void updateShape(ShapesType const& shape) { _shape = shape; };
    //void updateRadius(float radius);

private:
    std::vector<SingleBoid> _boids{};
    //ShapesType              _shape{};
};
