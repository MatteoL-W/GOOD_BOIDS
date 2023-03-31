#include "BoidsManager.h"

void BoidsManager::addSpecies(p6::Context& ctx, Species& species)
{
    for (int i = 0; i < species._quantity; i++)
        _boids.emplace_back(
            _speciesCounter,
            Utils::TransformAttributes{
                ._position = glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
                ._velocity = glm::vec2{p6::random::number(-0.001f, 0.001f), p6::random::number(-0.001f, 0.001f)},
            },
            species._shape,
            species._behaviorConfig,
            species._forcesConfig
        );

    _speciesCounter++;
}

void BoidsManager::update(ObstaclesManager const& obstacles, FoodProvider& foodProvider)
{
    for (auto& boid : _boids)
        boid.update(_boids, obstacles, foodProvider);
}

void BoidsManager::draw(p6::Context& ctx)
{
    for (auto& boid : _boids)
        boid.draw(ctx);
}

void BoidsManager::updateForcesConfig(ForcesConfig const& config)
{
    // ToDo: Verify species
    for (auto& boid : _boids)
        boid.setForcesConfig(config);
}

void BoidsManager::updateBehaviorConfig(BehaviorConfig const& config)
{
    // ToDo: Verify species
    for (auto& boid : _boids)
        boid.setBehaviorConfig(config);
}
