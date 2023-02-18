#include "Triangle.h"
#include "../utils/vec.hpp"

namespace Shapes {

Triangle::Triangle(glm::vec2 const& position, float const& radius)
    : _position(position), _velocity(p6::random::number(-1, 1), p6::random::number(-1, 1)), _acceleration(0, 0), _radius(radius)
{}

void Triangle::update(p6::Context& ctx, const std::vector<Shapes::Triangle>& _triangles)
{
    std::vector<Triangle> const closeMembers = getNearbyTriangles(_triangles);
    _acceleration += computeSeparationForce(closeMembers);

    _velocity += _acceleration;
    utils::vec::limit(_velocity, _maxSpeed);
    _position += _velocity * glm::vec2(0.01);

    keepTriangleInTheScreen(ctx);
    _acceleration *= 0;
}

void Triangle::draw(p6::Context& ctx)
{
    ctx.fill = {1, 1, 1, 1};
    ctx.equilateral_triangle(
        p6::Center{_position},
        p6::Radius{_radius},
        p6::Rotation{p6::Angle{_velocity}}
    );
}

glm::vec2 Triangle::computeSeparationForce(const std::vector<Shapes::Triangle>& _triangles)
{
    glm::vec2 force;

    for (auto const& closeMember : _triangles)
        force += glm::normalize(_position - closeMember._position) / glm::distance(_position, closeMember._position);

    return force;
}

std::vector<Triangle> Triangle::getNearbyTriangles(std::vector<Shapes::Triangle> const& triangles, double radius)
{
    // ToDo : OctTree / BVH ?
    std::vector<Triangle> nearbyTriangles{};
    for (const auto& triangle : triangles)
    {
        if (triangle._position == _position)
            continue;

        if (glm::distance(_position, triangle._position) < radius)
            nearbyTriangles.push_back(triangle);
    }
    return nearbyTriangles;
}

void Triangle::keepTriangleInTheScreen(const p6::Context& ctx)
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