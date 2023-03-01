#include "Obstacles.h"

void Obstacles::draw(p6::Context& ctx)
{
    for (auto const& obstacle : _obstacles)
    {
        // ToDo : Compat with 2D
        ctx.fill = {1, 1, 1, 1};
        ctx.circle(
            p6::Center{obstacle._position},
            p6::Radius{obstacle._radius}
        );
    }
}
void Obstacles::addRange(glm::vec2 start, glm::vec2 end, float radius)
{
    const float NB_ITERATIONS = std::ceil(glm::distance(start, end)) * 6;
    for (int i = 0; i <= NB_ITERATIONS; i++)
        _obstacles.push_back(Obstacle{glm::vec2{start + (end - start) * (i / NB_ITERATIONS)}, radius});
}
