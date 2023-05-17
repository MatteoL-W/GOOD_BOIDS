#pragma once

#include <p6/p6.h>
#include <chrono>
#include <vector>
#include "Rendering/Shapes/ShapesRegister.h"
#include "utils/StrongType.h"

namespace Features {
using Clock = std::chrono::high_resolution_clock;

struct ObstaclesConfig {
    /// The obstacles providing interval in seconds.
    int _providingInterval = 6;

    /// The number of obstacles dropping every interval
    int _drops = 2;

    /// The radius of the obstacles
    float _radius = 0.10f;

    /// The height the drop will lose every tick
    float _fallingFactor = 0.02f;
};

struct SphereObstacle {
    glm::vec3 _position{};
    float     _radius{};
    bool      _visible = true;
};

class ObstaclesManager {
public:
    explicit ObstaclesManager(ObstaclesConfig const& config, bool enableDropsInstantly = true);

    void update(SceneRadius& sceneRadius);
    void draw(utils::RenderingDatas&);
    void addOne(glm::vec3 pos, float radius = 0.1f);
    void enableDrop() { _randomDropStartTime = Clock::now(); };

    std::vector<SphereObstacle> const& getObstacles() const { return _obstacles; };
    ObstaclesConfig&                   getConfig() { return _config; };

private:
    /// Add a new food randomly inside the map
    void addObstaclesRandomly(SceneRadius&);

private:
    std::vector<SphereObstacle>      _obstacles;
    std::optional<Clock::time_point> _randomDropStartTime;
    ObstaclesConfig                  _config{};
};

} // namespace Features
