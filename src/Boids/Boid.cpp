#include "Boid.h"
#include <variant>
#include "utils/boidsForces.h"
#include "utils/vec.h"

Boid::Boid(unsigned int speciesId, utils::TransformAttributes const& transformAttributes, ShapesType const& shape, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _speciesId(speciesId), _transformAttributes(transformAttributes), _shape(shape), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

float Boid::getRadius() const
{
    float radius = 0.f;
    std::visit([&](auto shape) { radius += shape.getRadius(); }, _shape);
    return radius;
}

void Boid::update(std::vector<Boid> const& boids, ObstaclesManager const& obstacles, FoodProvider& foodProvider)
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

void Boid::draw(p6::Context& ctx)
{
    std::visit(
        [&](auto shape) {
            ctx.use_stroke = false;
            ctx.fill       = {1, 1, 1, 1};
            shape.draw(ctx, getTransformAttributes());
        },
        _shape
    );
}

void Boid::addFoodAttraction(FoodProvider& foodProvider)
{
    addToAcceleration(utils::boidsForces::computeFoodAttraction(*this, foodProvider, _behaviorConfig._foodAttractionRadius)); // ToDo : * _config._food_attraction_strength;);
}

void Boid::addObstaclesAvoidance(ObstaclesManager const& obstacles)
{
    addToAcceleration(utils::boidsForces::computeObstaclesAvoidance(*this, obstacles)); // ToDo : * _config._food_attraction_strength;);
}

void Boid::addClassicBoidsForces(std::vector<Boid> const& boids)
{
    auto const separation = utils::boidsForces::computeSeparationForce(*this, getNearbyBoids(boids, _forcesConfig._separationRadius)) * _forcesConfig._separationFactor;
    auto const alignment  = utils::boidsForces::computeAlignmentForce(*this, getNearbyAndSameBoids(boids, _forcesConfig._alignmentRadius)) * _forcesConfig._alignmentFactor;
    auto const cohesion   = utils::boidsForces::computeCohesionForce(*this, getNearbyAndSameBoids(boids, _forcesConfig._cohesionRadius)) * _forcesConfig._cohesionFactor;

    addToAcceleration(separation);
    addToAcceleration(alignment);
    addToAcceleration(cohesion);
}

static std::vector<Boid> getNearbyBoidsFromBoid(
    Boid const&                        scannedBoid,
    std::vector<Boid> const&           otherBoids,
    double                             maxDistance,
    std::optional<unsigned int> const& speciesId
)
{
    std::vector<Boid> nearbyBoids{};
    for (const auto& boid : otherBoids)
    {
        if (boid.getPosition() == scannedBoid.getPosition())
            continue;

        // If no species is specified, we add every close boids.
        // If a species is specified, we add close boids having this species.
        float const actualDistance = glm::distance(scannedBoid.getPosition(), boid.getPosition()) - boid.getRadius() - scannedBoid.getRadius();
        bool const  hasSameSpecies = speciesId.has_value() && boid.getSpeciesId() == speciesId.value();
        if (actualDistance < maxDistance && (!speciesId.has_value() || hasSameSpecies))
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}

std::vector<Boid> Boid::getNearbyBoids(std::vector<Boid> const& boids, double radius) const
{
    return getNearbyBoidsFromBoid(*this, boids, radius, std::nullopt);
}

std::vector<Boid> Boid::getNearbyAndSameBoids(std::vector<Boid> const& boids, double radius) const
{
    return getNearbyBoidsFromBoid(*this, boids, radius, getSpeciesId());
}
