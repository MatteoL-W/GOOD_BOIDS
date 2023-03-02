#include "SingleBoid.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(Movement const& movement, Config const& config)
    : _movement(movement), _config(config)
{}

void SingleBoid::update(std::vector<SingleBoid> const& boids, Obstacles const& obstacles)
{
    addObstaclesForce(obstacles);
    addClassicBoidsForces(boids);

    addToVelocity(getAcceleration());
    utils::vec::constrain(_movement._velocity, _config._minSpeed, _config._maxSpeed);

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
        const float distance        = glm::distance(obstacle._position, getPosition()) - (getRadius() / 2);
        const float avoidanceRadius = obstacle._radius * 2.f;
        if (distance > avoidanceRadius)
            continue;

        float strength = 0;

        const float maxAvoidanceRadius = obstacle._radius * 0.8f;
        if (distance < maxAvoidanceRadius)
            strength = 1.0f / (distance * distance); // Compute a more drastic strength if the boid is inside the obstacle.
        else
            strength = glm::clamp((avoidanceRadius - distance) / avoidanceRadius, 0.0f, 1.0f); // Calculate a strength value based on how close the boid is to the obstacle

        auto direction = glm::normalize(getPosition() - obstacle._position);
        force += direction * strength;
    }

    return force;
}

glm::vec2 SingleBoid::computeSeparationForce(std::vector<SingleBoid> const& boids) const
{
    auto force = glm::vec2{};

    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _config._separation_radius);
    for (auto const& closeMember : closeMembers)
        force += glm::normalize(getPosition() - closeMember.getPosition()) / glm::distance(getPosition(), closeMember.getPosition());

    return force * _config._avoid_factor;
}

glm::vec2 SingleBoid::computeAlignmentForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _config._alignment_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averageVelocity = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeMembers.size());
    return (averageVelocity - getVelocity()) * _config._matching_factor;
}

glm::vec2 SingleBoid::computeCohesionForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _config._cohesion_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averagePosition = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averagePosition += glm::normalize(closeMember.getPosition());

    averagePosition /= static_cast<float>(closeMembers.size());
    return (averagePosition - getPosition()) * _config._centering_factor;
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    // ToDo : OctTree / BVH ?
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