#include "Boids.h"

void Boids::addSpecies(p6::Context& ctx, unsigned int quantity, Species const& species, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
{
    for (unsigned int i = 0; i < quantity; i++)
        _boids.emplace_back(
            TransformAttributes{
                ._position = glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
                ._velocity = glm::vec2{p6::random::number(-0.001, 0.001), p6::random::number(-0.01, 0.01)},
            },
            species,
            behaviorConfig,
            forcesConfig
        );
}

void Boids::updateAndDraw(p6::Context& ctx, Obstacles const& obstacles, FoodProvider& foodProvider)
{
    for (auto& boid : _boids)
    {
        boid.update(_boids, obstacles, foodProvider);
        boid.draw(ctx);
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

/*
void Boids::updateRadius(float radius)
{
    std::visit([&](auto& shape) {
        shape.setRadius(radius);
    },
               _shape);
}*/
