#include "SingleBoid.h"
#include "utils/boidsForces.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(utils::TransformAttributes const& transformAttributes, Species const& species, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _transformAttributes(transformAttributes), _species(species), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

void SingleBoid::update(std::vector<SingleBoid> const& boids, Obstacles const& obstacles, FoodProvider& foodProvider)
{
    // Add forces to acceleration
    addFoodAttraction(foodProvider);
    addObstaclesAvoidance(obstacles);
    addClassicBoidsForces(boids);

    addToVelocity(getAcceleration());
    utils::vec::constrain(_transformAttributes._velocity, _behaviorConfig._minSpeed, _behaviorConfig._maxSpeed);

    addToPosition(getVelocity());
    resetForces();
}

void SingleBoid::draw(p6::Context& ctx)
{
    std::visit([&](auto shape) {
        ctx.use_stroke = false;
        ctx.fill       = {1, 1, 1, 1};
        shape.draw(ctx, getTransformAttributes());
    }, _species.getShape());
}

void SingleBoid::addFoodAttraction(FoodProvider& foodProvider)
{
    addToAcceleration(utils::boidsForces::computeFoodAttraction(*this, foodProvider, _behaviorConfig._foodAttractionRadius)); //  * _config._food_attraction_strength;);
}

void SingleBoid::addObstaclesAvoidance(Obstacles const& obstacles)
{
    addToAcceleration(utils::boidsForces::computeObstaclesAvoidance(*this, obstacles)); //  * _config._food_attraction_strength;);
}

void SingleBoid::addClassicBoidsForces(std::vector<SingleBoid> const& boids)
{
    auto const separation = utils::boidsForces::computeSeparationForce(*this, getNearbyBoids(boids, _forcesConfig._separationRadius)) * _forcesConfig._avoidFactor;
    auto const alignment  = utils::boidsForces::computeAlignmentForce(*this, getNearbyBoids(boids, _forcesConfig._alignmentRadius)) * _forcesConfig._matchingFactor;
    auto const cohesion   = utils::boidsForces::computeCohesionForce(*this, getNearbyBoids(boids, _forcesConfig._cohesionRadius)) * _forcesConfig._centeringFactor;

    addToAcceleration(separation);
    addToAcceleration(alignment);
    addToAcceleration(cohesion);
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    return getNearbyBoidsFromPosition(getPosition(), boids, radius);
}

std::vector<SingleBoid> getNearbyBoidsFromPosition(glm::vec2 const& position, std::vector<SingleBoid> const& boids, double radius)
{
    std::vector<SingleBoid> nearbyBoids{};
    for (const auto& boid : boids)
    {
        if (boid.getPosition() == position)
            continue;

        if (glm::distance(position, boid.getPosition()) < radius)
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}
