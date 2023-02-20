#pragma once

#include <variant>
#include "Shapes/2D.h"
#include "SingleBoid.h"
#include "p6/p6.h"

using ShapesType = std::variant<Shapes::TwoDimensions::Triangle>;

class Boids {
public:
    // ToDo: Do something to avoid the context ?
    Boids() = default;
    Boids(p6::Context&, unsigned int quantity, Config, ShapesType);

    void updateAndDraw(p6::Context&);
    void updateConfig(Config);

private:
    std::vector<SingleBoid> _boids{};
    ShapesType              _shape{};
};
