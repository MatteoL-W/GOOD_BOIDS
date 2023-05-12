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

    Spectator::getControlsInstance().handleEvents(ctx, _marker._up, _marker._front, _marker._left);
}

void ThirdPerson::computeDirectionVectors()
{
    _marker._front = glm::vec3{cos(_verticalRotation) * sin(_horizontalRotation), sin(_verticalRotation), cos(_verticalRotation) * cos(_horizontalRotation)};
    _marker._left  = glm::vec3{sin(_horizontalRotation + p6::PI / 2), 0, cos(_horizontalRotation + p6::PI / 2)};
    _marker. _up    = glm::cross(_marker._front, _marker._left);
}

} // namespace Camera