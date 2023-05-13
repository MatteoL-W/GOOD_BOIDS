#include "Boid.h"
#include <variant>
#include "Boids/Iterator/ForEachBoidMovement.h"

namespace Boids {


Boid::Boid(Species& species, const utils::TransformAttributes& transformAttributes)
: _species(species), _movement(species._id, transformAttributes, species._behaviorConfig, species._forcesConfig)
{}

void Boid::update(std::vector<Boid> const& boids, Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider, float sceneRadius)
{
    auto const boidsIterator = Iterator::ForEachBoidMovement<Boid>{boids};
    _movement.update(boidsIterator, obstacles, foodProvider, sceneRadius, getRadius());
}

void Boid::draw(utils::RenderingDatas& renderingDatas)
{
    std::visit(
        [&](auto const& shape) {
            shape.draw(_movement.getTransformAttributes(), renderingDatas);
        },
        _species._shape
    );
}

float Boid::getRadius() const
{
    float radius = 0.f;
    std::visit([&](auto const& shape) { radius = shape.getRadius(); }, _species._shape);
    return radius;
}

} // namespace Boids