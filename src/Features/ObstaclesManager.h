#pragma once

#include <p6/p6.h>
#include <vector>
#include "Rendering/Shapes/ShapesRegister.h"

namespace Features {

struct SphereObstacle {
    glm::vec3                  _position{};
    float                      _radius{};
    bool                       _visible = true;
    ObstaclesShapesType const& _shape{Rendering::Shapes::getObstacleShapeInstance()};
};

class ObstaclesManager {
public:
    explicit ObstaclesManager(std::vector<SphereObstacle> const& obstacles = {})
        : _obstacles(obstacles){};

    void draw();
    void addOne(glm::vec3 pos, float radius = 0.1f);
    void addRange(glm::vec3 start, glm::vec3 end, float radius = 0.1f);

    std::vector<SphereObstacle> const& getObstacles() const { return _obstacles; };

private:
    std::vector<SphereObstacle> _obstacles;
};

} // namespace Features
