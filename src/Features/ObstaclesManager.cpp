#include "ObstaclesManager.h"
#include "Shapes/3D.h"

namespace Features {

void ObstaclesManager::draw(p6::Context& ctx)
{
    for (auto const& obstacle : _obstacles)
    {
        auto obstacleShape = Shapes::ThreeDimensions::Sphere{obstacle._radius};
        //obstacleShape.draw(ctx, Utils::TransformAttributes{obstacle._position});
    }
}

void ObstaclesManager::addOne(glm::vec3 pos, float radius)
{
    _obstacles.push_back(Obstacle{glm::vec3{pos}, radius});
}

void ObstaclesManager::addRange(glm::vec3 start, glm::vec3 end, float radius)
{
    const float NB_ITERATIONS = std::ceil(glm::distance(start, end)) * 6;
    for (int i = 0; i <= NB_ITERATIONS; i++)
        _obstacles.push_back(Obstacle{glm::vec3{start + (end - start) * (i / NB_ITERATIONS)}, radius});
}

// void ObstaclesManager::add2DMapDelimiters(float screenHalfWidth, float screenHalfHeight)
//{
//     static float constexpr obstacleRadius = .1f;
//     addRange({-screenHalfWidth, screenHalfHeight + obstacleRadius}, {screenHalfWidth, screenHalfHeight + obstacleRadius}, obstacleRadius);
//     addRange({-screenHalfWidth, -screenHalfHeight - obstacleRadius}, {screenHalfWidth, -screenHalfHeight - obstacleRadius}, obstacleRadius);
//     addRange({-screenHalfWidth - obstacleRadius, -screenHalfHeight}, {-screenHalfWidth - obstacleRadius, screenHalfHeight}, obstacleRadius);
//     addRange({screenHalfWidth + obstacleRadius, -screenHalfHeight}, {screenHalfWidth + obstacleRadius, screenHalfHeight}, obstacleRadius);
// }

} // namespace Features