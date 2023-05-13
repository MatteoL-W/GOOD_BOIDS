#include "Manager.h"

namespace Boids {

void Manager::addSpecies(p6::Context& ctx, Species& species)
{
    for (int i = 0; i < species._quantity; i++)
        _boids.emplace_back(
            species,
            utils::TransformAttributes{
                ._position = glm::vec3{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1), p6::random::number(-1, 1)},
                ._velocity = glm::vec3{p6::random::number(-0.001f, 0.001f), p6::random::number(-0.001f, 0.001f), p6::random::number(-1, 1)},
            }
        );
}

void Manager::update(Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider, float sceneRadius)
{
    for (auto& boid : _boids)
        boid.update(_boids, obstacles, foodProvider, sceneRadius);
}

void Manager::draw(utils::RenderingDatas renderingDatas)
{
    for (auto& boid : _boids)
        boid.draw(renderingDatas);
}

} // namespace Boids