#include "Obstacles.h"
#include "Shapes/2D.h"

void Obstacles::draw(p6::Context& ctx)
{
    for (auto const& obstacle : _obstacles)
    {
        auto obstacleShape = Shapes::TwoDimensions::Circle{obstacle._radius};
        obstacleShape.draw(ctx, TransformAttributes{obstacle._position});
    }
}

void Obstacles::addOne(glm::vec2 pos, float radius)
{
    _obstacles.push_back(Obstacle{glm::vec2{pos}, radius});
}

void Obstacles::addRange(glm::vec2 start, glm::vec2 end, float radius)
{
    const float NB_ITERATIONS = std::ceil(glm::distance(start, end)) * 6;
    for (int i = 0; i <= NB_ITERATIONS; i++)
        _obstacles.push_back(Obstacle{glm::vec2{start + (end - start) * (i / NB_ITERATIONS)}, radius});
}
