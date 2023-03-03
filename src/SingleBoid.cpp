#include "SingleBoid.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(Movement const& movement, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _movement(movement), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

void SingleBoid::update(std::vector<SingleBoid> const& boids, Obstacles const& obstacles)
{
    addObstaclesForce(obstacles);
    addClassicBoidsForces(boids);

    addToVelocity(getAcceleration());
    utils::vec::constrain(_movement._velocity, _behaviorConfig._minSpeed, _behaviorConfig._maxSpeed);

    addToPosition(getVelocity());

    resetForces();
}

void SingleBoid::addObstaclesForce(const Obstacles& obstacles)
{
    addToAcceleration(computeObstaclesForce(obstacles));
}

void SingleBoid::addClassicBoidsForces(std::vector<SingleBoid> const& boids)
{
    addToAcceleration(computeSeparationForce(boids));
    addToAcceleration(computeAlignmentForce(boids));
    addToAcceleration(computeCohesionForce(boids));
}

glm::vec2 SingleBoid::computeObstaclesForce(Obstacles const& obstacles) const
{
    auto force = glm::vec2{};

    for (auto const& obstacle : obstacles.getAll())
    {
        const float distanceToObstacle = glm::distance(obstacle._position, getPosition());
        const float avoidanceRadius    = obstacle._radius * 2.5f;
        if (distanceToObstacle > avoidanceRadius)
            continue;

        // Calculate a avoidanceStrength value based on how close the boid is to the obstacle
        const float avoidanceStrength = glm::clamp((avoidanceRadius - distanceToObstacle) / avoidanceRadius, 0.0f, 1.0f);
        const auto directionToObstacle         = glm::normalize(getPosition() - obstacle._position);
        const auto fartherPositionFromObstacle = getPosition() + directionToObstacle * avoidanceRadius;
        const auto avoidanceVelocity           = glm::normalize(fartherPositionFromObstacle - getPosition());
        const auto steeringForceFromAvoidance  = avoidanceVelocity - getVelocity();
        force += glm::normalize(steeringForceFromAvoidance + directionToObstacle * avoidanceStrength) * avoidanceStrength;
    }

    return force;
}

glm::vec2 SingleBoid::computeSeparationForce(std::vector<SingleBoid> const& boids) const
{
    auto force = glm::vec2{};

    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._separation_radius);
    for (auto const& closeMember : closeMembers)
        force += glm::normalize(getPosition() - closeMember.getPosition()) / glm::distance(getPosition(), closeMember.getPosition());

    return force * _forcesConfig._avoid_factor;
}

glm::vec2 SingleBoid::computeAlignmentForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._alignment_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averageVelocity = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeMembers.size());
    return (averageVelocity - getVelocity()) * _forcesConfig._matching_factor;
}

glm::vec2 SingleBoid::computeCohesionForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._cohesion_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averagePosition = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averagePosition += glm::normalize(closeMember.getPosition());

    averagePosition /= static_cast<float>(closeMembers.size());
    return (averagePosition - getPosition()) * _forcesConfig._centering_factor;
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    std::vector<SingleBoid> nearbyBoids{};
    for (const auto& boid : boids)
    {
        if (boid.getPosition() == getPosition())
            continue;

        if (glm::distance(getPosition(), boid.getPosition()) < radius)
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}