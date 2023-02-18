#include "Boids.h"
Boids::Boids(p6::Context& ctx, unsigned int quantity)
{
    for (unsigned int i = 0; i < quantity; i++)
    {
        _triangles.emplace_back(
            glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)}, 0.05
        );
    }
}

void Boids::updateAndDraw(p6::Context& ctx)
{
    for (auto& triangle : _triangles)
    {
        triangle.update(ctx, _triangles);
        triangle.draw(ctx);
    }
}
