#include "SingleBoid.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(Movement const& movement, Config const& config)
    : _movement(movement), _config(config)
{}

void SingleBoid::update(p6::Context& ctx, std::vector<SingleBoid> const& boids, Obstacles const& obstacles)
{
    applyObstaclesForces(obstacles);
    applySteeringForces(boids);
    addToVelocity(_movement._acceleration);
    utils::vec::limit(_movement._velocity, _config._maxSpeed);

    addToPosition(getVelocity());

    keepInTheScreen(ctx);
    setAcceleration(glm::vec2{0});
}

void SingleBoid::applyObstaclesForces(Obstacles const& obstacles)
{
    addToAcceleration(computeObstaclesForce(obstacles));
}

void SingleBoid::applySteeringForces(std::vector<SingleBoid> const& boids)
{
    addToAcceleration(computeSeparationForce(boids));
    addToAcceleration(computeAlignmentForce(boids));
    addToAcceleration(computeCohesionForce(boids));
}

glm::vec2 SingleBoid::computeObstaclesForce(Obstacles const& obstacles) const
{
    auto force = glm::vec2{};
    for (auto const& obstacle : obstacles.getAll()) {
        const float distance = glm::distance(obstacle._position, getPosition());

        if (distance < obstacle._radius) {
            // Compute a force that repels the boid from the obstacle using inverse square law
            const glm::vec2 direction = glm::normalize(getPosition() - obstacle._position);
            const float strength = 1.0f / (distance * distance);
            force += direction * strength;
        }

    }
    return force;
}

glm::vec2 SingleBoid::computeSeparationForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _config._separation_radius);
    auto                          force        = glm::vec2{};

    for (auto const& closeMember : closeMembers)
        force += glm::normalize(getPosition() - closeMember.getPosition()) / glm::distance(getPosition(), closeMember.getPosition());

    return force;
}

glm::vec2 SingleBoid::computeAlignmentForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _config._alignment_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averageDirection = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averageDirection += closeMember.getVelocity();

    return averageDirection / static_cast<float>(closeMembers.size());
}

glm::vec2 SingleBoid::computeCohesionForce(std::vector<SingleBoid> const& boids) const
{
    // ToDo : Handle screen separation
    auto                          averagePosition = glm::vec2{};
    std::vector<SingleBoid> const closeMembers    = getNearbyBoids(boids, _config._cohesion_radius);
    if (closeMembers.empty())
        return averagePosition;

    for (auto const& closeMember : closeMembers)
        averagePosition += closeMember.getPosition();

    return averagePosition / static_cast<float>(closeMembers.size());
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

void SingleBoid::keepInTheScreen(p6::Context const& ctx)
{
    if (getPosition().x > ctx.aspect_ratio())
        _movement._position.x -= 2 * ctx.aspect_ratio();

    if (getPosition().y > 1)
        _movement._position.y -= 2 * 1;

    if (getPosition().x < -ctx.aspect_ratio())
        _movement._position.x += 2 * ctx.aspect_ratio();

    if (getPosition().y < -1)
        _movement._position.y += 2;
}
