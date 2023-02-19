#include "Boids.h"

Boids::Boids(p6::Context& ctx, unsigned int quantity, Config config)
{
    for (unsigned int i = 0; i < quantity; i++)
    {
        _boids.emplace_back(
            Movement{
                ._position = glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
                ._velocity = glm::vec2{p6::random::number(-1, 1), p6::random::number(-1, 1)},
            },
            config
        );
    }
}

void Boids::updateAndDraw(p6::Context& ctx)
{
    for (auto& boid : _boids)
    {
        boid.update(ctx, _boids);
        boid.draw(ctx);
    }
}
