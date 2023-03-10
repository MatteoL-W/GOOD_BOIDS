#pragma once

#include <p6/p6.h>
#include <vector>

struct Obstacle {
    glm::vec2 _position;
    float     _radius;
};

// ToDo: Don't use a class, just do some functions
class Obstacles {
public:
    Obstacles() = default;
    explicit Obstacles(std::vector<Obstacle> const& obstacles)
        : _obstacles(obstacles){};

    void                  draw(p6::Context&);
    void                  addRange(glm::vec2 start, glm::vec2 end, float radius = 0.1f);
    std::vector<Obstacle> getAll() const { return _obstacles; };

private:
    std::vector<Obstacle> _obstacles;
};