#include "ObstaclesManager.h"
#include "Rendering/Shapes/ShapesRegister.h"

namespace Features {

// ToDO Visible ?????

ObstaclesManager::ObstaclesManager(const ObstaclesConfig& config, bool enableDropsInstantly)
    : _config(config)
{
    if (enableDropsInstantly)
        enableDrop();
}

void ObstaclesManager::update(SceneRadius& sceneRadius)
{
    if (!_obstacles.empty())
    {
        // Erase obstacles that meet the condition
        _obstacles.erase(
            std::remove_if(_obstacles.begin(), _obstacles.end(), [&](SphereObstacle const& obstacle) { return obstacle._position.y < -sceneRadius.value; }),
            _obstacles.end()
        );

        // Modify remaining obstacles
        for (auto& obstacle : _obstacles)
            if (!obstacle._isStaticAndInvisible)
                obstacle._position.y -= _config._fallingFactor;
    }

    if (!_randomDropStartTime.has_value())
        return;

    auto current_time = Clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - *_randomDropStartTime).count();
    if (elapsed_time >= _config._providingInterval)
    {
        addObstaclesRandomly(sceneRadius);
        _randomDropStartTime = current_time;
    }
}

void ObstaclesManager::addObstaclesRandomly(SceneRadius& sceneRadius)
{
    for (int i = 0; i < _config._drops; i++)
    {
        auto randomPosition = glm::vec3{
            p6::random::number(-sceneRadius.value, sceneRadius.value),
            sceneRadius.value,
            p6::random::number(-sceneRadius.value, sceneRadius.value)};
        addOne(randomPosition, _config._radius);
    }
}

void ObstaclesManager::draw(utils::RenderingDatas& renderingDatas)
{
    ObstaclesShapesType const& shape = Rendering::Shapes::getDropShapeInstance();
    for (auto const& obstacle : _obstacles)
    {
        std::visit(
            [&](auto const& sphereShape) {
                if (!obstacle._isStaticAndInvisible)
                    sphereShape.draw(utils::TransformAttributes{obstacle._position}, renderingDatas);
            },
            shape
        );
    }
}

void ObstaclesManager::addOne(glm::vec3 pos, float radius, bool isStaticAndInvisible)
{
    _obstacles.push_back({._position = glm::vec3{pos}, ._radius = radius, ._isStaticAndInvisible = isStaticAndInvisible});
}

} // namespace Features