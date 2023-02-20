#pragma once

#include "SingleBoid.h"
#include "p6/p6.h"

class Boids {
public:
    // ToDo: Abstract Shape
    // ToDo: Do something to avoid the context ?
    Boids() = default;
    Boids(p6::Context&, unsigned int quantity, Config);
    void updateAndDraw(p6::Context&);
    void updateConfig(Config);

private:
    std::vector<SingleBoid> _boids{};
};
