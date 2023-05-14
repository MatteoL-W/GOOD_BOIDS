#include "ObstaclesManager.h"
#include "Rendering/Shapes/ShapesRegister.h"

namespace Features {

void ObstaclesManager::draw()
{
    auto renderingDatas = utils::RenderingDatas{._renderType = utils::RenderType::Classic};
    for (auto const& obstacle : _obstacles)
    {
        if (!obstacle._visible)
            return;

        std::visit(
            [&](auto const& sphereShape) {
                sphereShape.draw(utils::TransformAttributes{obstacle._position}, renderingDatas);
            },
            obstacle._shape
        );
    }
}

void ObstaclesManager::addOne(glm::vec3 pos, float radius)
{
    _obstacles.push_back(SphereObstacle{glm::vec3{pos}, radius});
}

void ObstaclesManager::addRange(glm::vec3 start, glm::vec3 end, float radius)
{
    float        distance         = glm::distance(start, end);
    unsigned int numObstacles     = static_cast<unsigned int>(distance / (2 * radius + 0.01f));
    float        obstacleDistance = distance / static_cast<float>(numObstacles);
    glm::vec3    direction        = glm::normalize(end - start);

    for (unsigned int i = 0; i < numObstacles; i++)
    {
        glm::vec3 position = start + direction * static_cast<float>(i) * obstacleDistance;
        addOne(position, radius);
    }
}

} // namespace Features