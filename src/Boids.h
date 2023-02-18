#pragma once

#include "Shapes/Triangle.h"
#include "p6/p6.h"

class Boids {
public:
    // ToDo: Abstract Shape
    // ToDo: Do something to avoid the context
    Boids() {};
    Boids(p6::Context&, unsigned int quantity);
    void updateAndDraw(p6::Context&);

private:
    std::vector<Shapes::Triangle> _triangles{};
};

