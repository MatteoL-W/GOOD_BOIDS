#include "Boids.h"

Boids::Boids(p6::Context& ctx, unsigned int quantity, ShapesType const& shape, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _shape(shape)
{
    for (unsigned int i = 0; i < quantity; i++)
        _boids.emplace_back(
            Movement{
                ._position = glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
                ._velocity = glm::vec2{p6::random::number(-1, 1), p6::random::number(-1, 1)},
            },
            behaviorConfig,
            forcesConfig
        );
}

void Boids::updateAndDraw(p6::Context& ctx, Obstacles const& obstacles, FoodProvider& foodProvider)
{
    for (auto& boid : _boids)
    {
        boid.update(_boids, obstacles, foodProvider);
        std::visit([&](auto shape) {
            ctx.use_stroke = false;
            ctx.fill       = {1, 1, 1, 1};
            shape.draw(ctx, boid.getMovement());
        }, _shape);
    }
}

void Boids::updateForcesConfig(ForcesConfig const& config)
{
    for (auto& boid : _boids)
        boid.setForcesConfig(config);
}

void Boids::updateBehaviorConfig(BehaviorConfig const& config)
{
    for (auto& boid : _boids)
        boid.setBehaviorConfig(config);
}

void Boids::updateRadius(float radius)
{
    std::visit([&](auto& shape) {
        shape.setRadius(radius);
    }, _shape);
}
