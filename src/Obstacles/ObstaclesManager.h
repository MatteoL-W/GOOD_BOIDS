#pragma once

#include <p6/p6.h>
#include <vector>

struct Obstacle {
    glm::vec3 _position;
    float     _radius;
};

class ObstaclesManager {
public:
    explicit ObstaclesManager(std::vector<Obstacle> const& obstacles = {})
        : _obstacles(obstacles){};

    void draw(p6::Context&);
    void addOne(glm::vec3 pos, float radius = 0.1f);
    void addRange(glm::vec3 start, glm::vec3 end, float radius = 0.1f);
    //void add2DMapDelimiters(float screenHalfWidth, float screenHalfHeight);

    std::vector<Obstacle> const& getObstacles() const { return _obstacles; };

private:
    std::vector<Obstacle> _obstacles;
};