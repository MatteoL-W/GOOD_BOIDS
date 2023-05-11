#include "ThirdPerson.h"

namespace Camera {

ThirdPerson::ThirdPerson()
{
    computeDirectionVectors();
}

void ThirdPerson::rotateLeft(float degrees)
{
    _horizontalRotation -= degrees * p6::PI / 180;
    computeDirectionVectors();
}

void ThirdPerson::rotateUp(float degrees)
{
    _verticalRotation += degrees * p6::PI / 180;
    computeDirectionVectors();
}

void ThirdPerson::handleEvents(p6::Context& ctx)
{
    ctx.mouse_moved = [&](p6::MouseMove move) {
        rotateLeft(move.delta.x * 100);
        rotateUp(move.delta.y * 100);
    };

    Spectator::getControlsInstance().handleEvents(ctx, _front, _left);
}

void ThirdPerson::computeDirectionVectors()
{
    _front = glm::vec3{cos(_verticalRotation) * sin(_horizontalRotation), sin(_verticalRotation), cos(_verticalRotation) * cos(_horizontalRotation)};
    _left  = glm::vec3{sin(_horizontalRotation + p6::PI / 2), 0, cos(_horizontalRotation + p6::PI / 2)};
    _up    = glm::cross(_front, _left);
}

} // namespace Camera