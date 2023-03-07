#pragma once

#include <variant>
#include "Obstacles/Obstacles.h"
#include "Shapes/2D.h"
#include "SingleBoid.h"
#include "p6/p6.h"

using ShapesType = std::variant<
    Shapes::TwoDimensions::Triangle,
    Shapes::TwoDimensions::Circle,
    Shapes::TwoDimensions::Fish>;

class Boids {
public:
    // ToDo: Do something to avoid the context ?
    Boids() = default;
    Boids(p6::Context&, unsigned int quantity, ShapesType const&, BehaviorConfig const&, ForcesConfig const&);

    void updateAndDraw(p6::Context&, Obstacles const&);
    void updateForcesConfig(ForcesConfig const&);
    void updateBehaviorConfig(BehaviorConfig const&);
    void updateShape(ShapesType const& shape) { _shape = shape; };
    void updateRadius(float radius);

private:
    std::vector<SingleBoid> _boids{};
    ShapesType              _shape{};
};