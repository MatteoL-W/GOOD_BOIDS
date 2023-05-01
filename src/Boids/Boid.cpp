#include "Boid.h"
#include <variant>
#include "Boids/Iterator/ForEachBoidMovement.h"

namespace Boids {

Boid::Boid(unsigned int speciesId, ShapesType const& shape, utils::TransformAttributes const& transformAttributes, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _speciesId(speciesId), _shape(shape), _movement(speciesId, transformAttributes, behaviorConfig, forcesConfig)
{}

void Boid::update(std::vector<Boid> const& boids, Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider)
{
    auto const boidsIterator = Iterator::ForEachBoidMovement<Boid>{boids};
    _movement.update(boidsIterator, obstacles, foodProvider, getRadius());
}

void Boid::draw(utils::RenderingDatas& renderingDatas)
{
    std::visit(
        [&](auto const& shape) {
            shape.draw(_movement.getTransformAttributes(), renderingDatas);
        },
        _shape
    );
}

float Boid::getRadius() const
{
    float radius = 0.f;
    std::visit([&](auto const& shape) { radius = shape.getRadius(); }, _shape);
    return radius;
}

} // namespace Boids