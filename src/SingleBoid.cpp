#include "SingleBoid.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(Movement const& movement, Config const& config)
    : _movement(movement), _config(config)
{}

void SingleBoid::update(p6::Context& ctx, std::vector<SingleBoid> const& boids)
{
    applySteeringForces(boids);

    addToPosition(getVelocity() * glm::vec2(0.01f));

    keepInTheScreen(ctx);
    setAcceleration(glm::vec2{0});
}

void SingleBoid::draw(p6::Context& ctx) const
{
    // ToDo : Abstract this
    ctx.fill = {1, 1, 1, 1};
    ctx.equilateral_triangle(
        p6::Center{getPosition()},
        p6::Radius{_config._radius},
        p6::Rotation{p6::Angle{getVelocity()}}
    );
}

void SingleBoid::applySteeringForces(std::vector<SingleBoid> const& boids)
{
    addToAcceleration(computeSeparationForce(boids));
    addToAcceleration(computeAlignmentForce(boids));
    addToAcceleration(computeCohesionForce(boids));

    addToVelocity(_movement._acceleration);
    utils::vec::limit(_movement._velocity, _config._maxSpeed);
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
