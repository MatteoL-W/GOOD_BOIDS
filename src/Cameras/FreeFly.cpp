#include "FreeFly.h"

namespace Camera {

FreeFly::FreeFly(glm::vec3 position, float horizontalRotation, float verticalRotation)
    : _position(position), _horizontalRotation(horizontalRotation), _verticalRotation(verticalRotation)
{
    computeDirectionVectors();
}

void FreeFly::computeDirectionVectors()
{
    _front = glm::vec3{cos(_verticalRotation) * sin(_horizontalRotation), sin(_verticalRotation), cos(_verticalRotation) * cos(_horizontalRotation)};
    _left  = glm::vec3{sin(_horizontalRotation + p6::PI / 2), 0, cos(_horizontalRotation + p6::PI / 2)};
    _up    = glm::cross(_front, _left);
}

void FreeFly::rotateLeft(float degrees)
{
    const auto radians = degrees * p6::PI / 180;
    _horizontalRotation -= radians;
    computeDirectionVectors();
}

void FreeFly::rotateUp(float degrees)
{
    const auto radians = degrees * p6::PI / 180;
    _verticalRotation += radians;
    computeDirectionVectors();
}

void FreeFly::handleEvents(p6::Context& ctx)
{
    ctx.mouse_moved = [&](p6::MouseMove move) {
        rotateLeft(move.delta.x * 100);
        rotateUp(move.delta.y * 100);
    };

    ctx.key_repeated = [&](p6::Key key) {
        const float step = .01f;

        switch (key.physical)
        {
        case GLFW_KEY_W:
            moveFront(step);
            break;
        case GLFW_KEY_S:
            moveFront(-step);
            break;
        case GLFW_KEY_A:
            moveLeft(-step);
            break;
        case GLFW_KEY_D:
            moveLeft(step);
            break;
        default:
            break;
        }
    };
}

} // namespace Camera