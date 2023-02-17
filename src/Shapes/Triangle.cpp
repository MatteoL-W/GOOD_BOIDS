#include "Triangle.h"

namespace Shapes {

Triangle::Triangle(glm::vec2 const& position, p6::Angle const& direction, float const& radius, float const& speed)
    : _position(position), _direction(direction), _radius(radius), _speed(speed)
{}

void Triangle::update(p6::Context& ctx, std::vector<Shapes::Triangle> _triangles)
{
    // computeSeparationForce(_triangles);
    avoidOthersMembers(_triangles);

    _position.x += std::cos(_direction.as_radians()) * _speed;
    _position.y += std::sin(_direction.as_radians()) * _speed;

    if (_position.x > ctx.aspect_ratio())
        _position.x -= 2 * ctx.aspect_ratio();

    if (_position.y > 1)
        _position.y -= 2 * 1;

    if (_position.x < -ctx.aspect_ratio())
        _position.x += 2 * ctx.aspect_ratio();

    if (_position.y < -1)
        _position.y += 2;
}

void Triangle::draw(p6::Context& ctx)
{
    ctx.fill = {1, 1, 1, 1};
    ctx.equilateral_triangle(
        p6::Center{_position},
        p6::Radius{_radius},
        p6::Rotation{_direction}
    );
}

void Triangle::avoidOthersMembers(std::vector<Shapes::Triangle> _triangles)
{
    auto      closeMembers = getNearbyTriangles(_triangles, 0.2f);

    for (auto const& closeMember : closeMembers) {
        _direction += p6::Angle{p6::Radians{M_PI/30}};
    }
}

glm::vec2 Triangle::computeSeparationForce(std::vector<Shapes::Triangle> _triangles)
{
    // ToDo : Verify
    glm::vec2 force;
    auto      closeMembers = getNearbyTriangles(_triangles);

    for (auto const& closeMember : closeMembers)
        force += (_position - closeMember._position) / glm::distance(_position, closeMember._position);

    return force;
}

std::vector<Triangle> Triangle::getNearbyTriangles(std::vector<Shapes::Triangle> const& triangles, double radius)
{
    // ToDo : OctTree / BVH ?
    std::vector<Triangle> nearbyTriangles{};
    for (const auto& triangle : triangles)
    {
        if (triangle._position == _position) {
            continue;
        }
        if (glm::distance(_position, triangle._position) < radius)
        {
            nearbyTriangles.push_back(triangle);
        }
    }
    return nearbyTriangles;
}


} // namespace Shapes