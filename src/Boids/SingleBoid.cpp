#include "SingleBoid.h"
#include <utility>
#include <variant>
#include "utils/boidsForces.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(std::string species, utils::TransformAttributes const& transformAttributes, ShapesType const& shape, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _species(std::move(species)), _transformAttributes(transformAttributes), _shape(shape), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

float SingleBoid::getRadius() const
{
    float radius = 0.f;
    std::visit([&](auto shape) { radius += shape.getRadius(); }, getShape());
    return radius;
}

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
    std::visit(
        [&](auto shape) {
            ctx.use_stroke = false;
            ctx.fill       = {1, 1, 1, 1};
            shape.draw(ctx, getTransformAttributes());
        },
        getShape()
    );
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
    auto const separation = utils::boidsForces::computeSeparationForce(*this, getNearbyBoids(boids, _forcesConfig._separationRadius)) * _forcesConfig._separationFactor;
    auto const alignment  = utils::boidsForces::computeAlignmentForce(*this, getNearbyAndSameBoids(boids, _forcesConfig._alignmentRadius)) * _forcesConfig._alignmentFactor;
    auto const cohesion   = utils::boidsForces::computeCohesionForce(*this, getNearbyAndSameBoids(boids, _forcesConfig._cohesionRadius)) * _forcesConfig._cohesionFactor;

    addToAcceleration(separation);
    addToAcceleration(alignment);
    addToAcceleration(cohesion);
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    return getNearbyBoidsFromBoid(*this, boids, radius, std::nullopt);
}

std::vector<SingleBoid> SingleBoid::getNearbyAndSameBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    return getNearbyBoidsFromBoid(*this, boids, radius, getSpecies());
}

std::vector<SingleBoid> getNearbyBoidsFromBoid(
    SingleBoid const&                 scannedBoid,
    std::vector<SingleBoid> const&    otherBoids,
    double                            maxDistance,
    std::optional<std::string> const& species
)
{
    std::vector<SingleBoid> nearbyBoids{};
    for (const auto& boid : otherBoids)
    {
        if (boid.getPosition() == scannedBoid.getPosition())
            continue;

        // If no species is specified, we add every close boids.
        // If a species is specified, we add close boids having this species.
        float const actualDistance = glm::distance(scannedBoid.getPosition(), boid.getPosition()) - boid.getRadius() - scannedBoid.getRadius();
        bool const  hasSameSpecies = species.has_value() && boid.getSpecies() == species.value();
        if (actualDistance < maxDistance && (!species.has_value() || hasSameSpecies))
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}
