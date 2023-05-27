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
        auto* window = ctx.underlying_glfw_window();
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            rotateLeft(move.delta.x * 100);
            rotateUp(move.delta.y * 100);
        }
    };
}

void ThirdPerson::computeDirectionVectors()
{
    _marker._front = glm::vec3{glm::cos(_verticalRotation) * glm::sin(_horizontalRotation), glm::sin(_verticalRotation), glm::cos(_verticalRotation) * glm::cos(_horizontalRotation)};
    _marker._left  = glm::vec3{glm::sin(_horizontalRotation + p6::PI / 2), 0.f, glm::cos(_horizontalRotation + p6::PI / 2)};
    _marker._up    = glm::cross(_marker._front, _marker._left);
}

} // namespace Camera