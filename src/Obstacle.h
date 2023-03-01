#pragma once

#include <p6/p6.h>
#include <vector>

struct Obstacle {
    glm::vec2 _position;
    float     _radius;
};

class Obstacles {
public:
    explicit Obstacles(std::vector<Obstacle> const& obstacles) : _obstacles(obstacles){};
    void draw(p6::Context& ctx)
    {
        for (auto const& obstacle : _obstacles) {
            // ToDo : Compat with 2D
            ctx.fill = {1, 1, 1, 1};
            ctx.circle(
                p6::Center{obstacle._position},
                p6::Radius{obstacle._radius}
            );
        }
    }

    std::vector<Obstacle> getAll() const { return _obstacles; };

private:
    std::vector<Obstacle> _obstacles;
};