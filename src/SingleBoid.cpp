#include "SingleBoid.h"
#include "utils/vec.hpp"

namespace Shapes {

SingleBoid::SingleBoid(glm::vec2 const& position, float const& radius)
    : _position(position), _velocity(p6::random::number(-1, 1), p6::random::number(-1, 1)), _radius(radius)
{}

void SingleBoid::update(p6::Context& ctx, const std::vector<Shapes::SingleBoid>& boids)
{
    applySteeringForces(boids);

    // ToDo : Ugly multiplication
    _position += _velocity * glm::vec2(0.01);

    keepBoidInTheScreen(ctx);
    _acceleration *= 0;
}

void SingleBoid::draw(p6::Context& ctx)
{
    // ToDo : Abstract this
    ctx.fill = {1, 1, 1, 1};
    ctx.equilateral_triangle(
        p6::Center{_position},
        p6::Radius{_radius},
        p6::Rotation{p6::Angle{_velocity}}
    );
}

void SingleBoid::applySteeringForces(const std::vector<Shapes::SingleBoid>& boids)
{
    _acceleration += computeSeparationForce(boids);
    _acceleration += computeAlignmentForce(boids);
    _acceleration += computeCohesionForce(boids);

    _velocity += _acceleration;
    utils::vec::limit(_velocity, _maxSpeed);
}

glm::vec2 SingleBoid::computeSeparationForce(const std::vector<Shapes::SingleBoid>& boids)
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, 0.1f);
    auto                          force        = glm::vec2{};

    for (auto const& closeMember : closeMembers)
        force += glm::normalize(_position - closeMember._position) / glm::distance(_position, closeMember._position);

    return force;
}

glm::vec2 SingleBoid::computeAlignmentForce(const std::vector<Shapes::SingleBoid>& boids)
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, 0.2f);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averageDirection = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averageDirection += closeMember._velocity;

    return averageDirection / static_cast<float>(closeMembers.size());
}

glm::vec2 SingleBoid::computeCohesionForce(const std::vector<Shapes::SingleBoid>& boids)
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, 0.1f);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averagePosition = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averagePosition += closeMember._position;

    return averagePosition / static_cast<float>(closeMembers.size());
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<Shapes::SingleBoid> const& boids, double radius)
{
    // ToDo : OctTree / BVH ?
    std::vector<SingleBoid> nearbyBoids{};
    for (const auto& boid : boids)
    {
        if (boid._position == _position)
            continue;

        if (glm::distance(_position, boid._position) < radius)
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}

void SingleBoid::keepBoidInTheScreen(const p6::Context& ctx)
{
    if (_position.x > ctx.aspect_ratio())
        _position.x -= 2 * ctx.aspect_ratio();

    if (_position.y > 1)
        _position.y -= 2 * 1;

    if (_position.x < -ctx.aspect_ratio())
        _position.x += 2 * ctx.aspect_ratio();

    if (_position.y < -1)
        _position.y += 2;
}

} // namespace Shapes