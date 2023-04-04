#include "BoidMovement.h"
#include "Utils/boidsForces.h"
#include "Utils/vec.h"

BoidMovement::BoidMovement(unsigned int speciesId, Utils::TransformAttributes const& transformAttributes, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _speciesId(speciesId), _transformAttributes(transformAttributes), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

void BoidMovement::update(IForEachBoidMovement const& boids, Features::ObstaclesManager const& obstacles, Features::FoodProvider& foodProvider, float boidRadius)
{
    // Add forces to acceleration
    addFoodAttraction(foodProvider);
    addObstaclesAvoidance(obstacles, boidRadius);
    addClassicBoidsForces(boids, boidRadius);

    addToVelocity(getAcceleration());
    Utils::vec::constrain(_transformAttributes._velocity, _behaviorConfig._minSpeed, _behaviorConfig._maxSpeed);

    addToPosition(getVelocity());
    resetForces();
}

void BoidMovement::addFoodAttraction(Features::FoodProvider& foodProvider)
{
    addToAcceleration(Utils::boidsForces::computeFoodAttraction(*this, foodProvider, _behaviorConfig._foodAttractionRadius)); // ToDo : * _config._food_attraction_strength;);
}

void BoidMovement::addObstaclesAvoidance(Features::ObstaclesManager const& obstacles, float boidRadius)
{
    addToAcceleration(Utils::boidsForces::computeObstaclesAvoidance(*this, obstacles, boidRadius)); // ToDo : * _config._food_attraction_strength;);
}

void BoidMovement::addClassicBoidsForces(IForEachBoidMovement const& boids, float boidRadius)
{
    auto const separation = Utils::boidsForces::computeSeparationForce(*this, getNearbyBoids(boids, boidRadius, _forcesConfig._separationRadius)) * _forcesConfig._separationFactor;
    auto const alignment  = Utils::boidsForces::computeAlignmentForce(*this, getNearbyAndSameBoids(boids, boidRadius, _forcesConfig._alignmentRadius)) * _forcesConfig._alignmentFactor;
    auto const cohesion   = Utils::boidsForces::computeCohesionForce(*this, getNearbyAndSameBoids(boids, boidRadius, _forcesConfig._cohesionRadius)) * _forcesConfig._cohesionFactor;

    addToAcceleration(separation);
    addToAcceleration(alignment);
    addToAcceleration(cohesion);
}

static std::vector<BoidMovement> getNearbyBoidsFromBoid(
    std::optional<unsigned int> const& speciesId,
    BoidMovement const&                scannedBoid,
    IForEachBoidMovement const&        boidsIterator,
    float                              boidRadius,
    float                              proximityRadius
)
{
    std::vector<BoidMovement> nearbyBoids{};
    boidsIterator.loop([&](BoidMovement const& boid) {
        if (boid.getPosition() == scannedBoid.getPosition())
            return;

        /// If no species is specified, we add every close boids.
        /// If a species is specified, we add close boids having this species.
        // ToDo: Ca devrait être scannedBoid.getRadius() à la place du 2eme boidRadius. Comment fix ?
        float const actualDistance = glm::distance(scannedBoid.getPosition(), boid.getPosition()) - boidRadius - boidRadius;
        bool const  hasSameSpecies = speciesId.has_value() && boid.getSpeciesId() == speciesId;
        if (actualDistance < proximityRadius && (!speciesId.has_value() || hasSameSpecies))
            nearbyBoids.push_back(boid);
    });
    return nearbyBoids;
}

std::vector<BoidMovement> BoidMovement::getNearbyBoids(IForEachBoidMovement const& boids, float boidRadius, float proximityRadius) const
{
    return getNearbyBoidsFromBoid(std::nullopt, *this, boids, boidRadius, proximityRadius);
}

std::vector<BoidMovement> BoidMovement::getNearbyAndSameBoids(IForEachBoidMovement const& boids, float boidRadius, float proximityRadius) const
{
    return getNearbyBoidsFromBoid(getSpeciesId(), *this, boids, boidRadius, proximityRadius);
}
