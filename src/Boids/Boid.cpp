#include "Boid.h"
#include <variant>
#include "Boids/ForEachBoidMovement.h"

// ToDo : Doublon speciesId ?
Boid::Boid(unsigned int speciesId, ShapesType const& shape, Utils::TransformAttributes const& transformAttributes, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _speciesId(speciesId), _shape(shape), _movement(speciesId, transformAttributes, behaviorConfig, forcesConfig)
{}

void Boid::update(std::vector<Boid> const& boids, Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider)
{
    auto const boidsIterator = ForEachBoidMovement<Boid>{boids};
    _movement.update(boidsIterator, obstacles, foodProvider, getRadius());
}

void Boid::draw(p6::Context& ctx)
{
    std::visit(
        [&](auto shape) {
            ctx.use_stroke = false;
            ctx.fill       = {1, 1, 1, 1};
            shape.draw(ctx, _movement.getTransformAttributes());
        },
        _shape
    );
}

float Boid::getRadius() const
{
    float radius = 0.f;
    std::visit([&](auto shape) { radius = shape.getRadius(); }, _shape);
    return radius;
}
