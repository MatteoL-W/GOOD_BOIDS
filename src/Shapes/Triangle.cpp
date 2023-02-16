#include "Triangle.h"

namespace Shapes {

Triangle::Triangle(glm::vec2 const& position, p6::Angle const& direction, float const& radius, float const& speed)
    : _position(position), _direction(direction), _radius(radius), _speed(speed)
{}

void Triangle::update(p6::Context& ctx)
{
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

std::vector<Triangle> Triangle::getNearbyTriangles(const std::vector<Shapes::Triangle>& triangles, double radius)
{
    // ToDo : OctTree / BVH ?
    std::vector<Triangle> nearbyTriangles{};
    for (const auto& triangle : triangles) {
        if (glm::distance(_position, triangle._position) < radius) {
            nearbyTriangles.push_back(triangle);
        }
    }
    return nearbyTriangles;
}

} // namespace Shapes