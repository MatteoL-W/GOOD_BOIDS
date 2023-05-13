#include "Manager.h"

namespace Boids {

void Manager::addSpecies(SceneRadius& sceneRadius, Species& species)
{
    for (int i = 0; i < species._quantity; i++)
        _boids.emplace_back(
            species,
            utils::TransformAttributes{
                ._position = glm::vec3{p6::random::number(-sceneRadius.value, sceneRadius.value), p6::random::number(-sceneRadius.value, sceneRadius.value), p6::random::number(-sceneRadius.value, sceneRadius.value)},
                ._velocity = glm::vec3{p6::random::number(-0.001f, 0.001f), p6::random::number(-0.001f, 0.001f), p6::random::number(-1, 1)},
            }
        );
}

void Manager::update(Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider, SceneRadius& sceneRadius)
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