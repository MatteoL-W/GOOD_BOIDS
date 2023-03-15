#include "Boids.h"

void Boids::addSpecies(p6::Context& ctx, SpeciesInitialization& speciesInitialization)
{
    for (int i = 0; i < speciesInitialization._quantity; i++)
        _boids.emplace_back(
            utils::TransformAttributes{
                ._position = glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
                ._velocity = glm::vec2{p6::random::number(-0.001, 0.001), p6::random::number(-0.01, 0.01)},
            },
            speciesInitialization._species,
            speciesInitialization._behaviorConfig,
            speciesInitialization._forcesConfig
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
