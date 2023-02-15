#include "Triangle.h"

namespace Shapes {

Triangle::Triangle(glm::vec2 const& position, p6::Angle const& direction, float const& radius)
    : _position(position), _direction(direction), _radius(radius)
{}

void Triangle::update(p6::Context& ctx)
{
    _position.x += std::cos(_direction.as_radians()) * 0.01;
    _position.y += std::sin(_direction.as_radians()) * 0.01;

    if (_position.x > ctx.aspect_ratio())
        _position.x = _position.x - 2 * ctx.aspect_ratio();

    if (_position.y > 1)
        _position.y = _position.y - 2 * 1;

    if (_position.x < -ctx.aspect_ratio())
        _position.x = ctx.aspect_ratio() - (_position.x + ctx.aspect_ratio());

    if (_position.y < -1)
        _position.y = 1 - (_position.y + 1);
}

void Triangle::draw(p6::Context& ctx)
{
    ctx.equilateral_triangle(
        p6::Center{_position},
        p6::Radius{_radius},
        p6::Rotation{_direction}
    );
}
} // namespace Shapes