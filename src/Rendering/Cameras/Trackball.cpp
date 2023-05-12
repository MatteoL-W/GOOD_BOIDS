#include "Trackball.h"
#include "Spectator/Controls.h"
#include "glpp-extended/lib/glm/glm/gtc/type_ptr.hpp"

namespace Camera {

glm::vec3 Trackball::getPosition() const
{
    // Convert angles to radians
    float const theta = glm::radians(_angleX);
    float const phi   = glm::radians(_angleY);

    // Calculate camera position in spherical coordinates
    float const x = _distance * glm::sin(phi) * glm::cos(theta);
    float const y = _distance * glm::sin(phi) * glm::sin(theta);
    float const z = _distance * glm::cos(phi);

    // Return camera position as a vector
    return {x, y, z};
}

glm::mat4 Trackball::getViewMatrix() const
{
    float const angleX = _angleX * (p6::PI / 180);
    float const angleY = _angleY * (p6::PI / 180);

    auto view = glm::mat4{1};
    view      = glm::translate(view, glm::vec3{0.f, 0.f, _distance});
    view      = glm::rotate(view, angleX, glm::vec3{0.f, 1.f, 0.f});  // car on tourne sur Y
    view      = glm::rotate(view, angleY, glm::vec3{-1.f, 0.f, 0.f}); // car on va vers le haut
    return view;
}

void Trackball::handleEvents(p6::Context& ctx)
{
    ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
        moveFront(scroll.dy);
    };

    ctx.mouse_dragged = [&](p6::MouseDrag drag) {
        auto* window = ctx.underlying_glfw_window();
        if (glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED)
        {
            rotateUp(drag.delta.y * 100);
            rotateLeft(drag.delta.x * 100);
        }
    };

    Spectator::getControlsInstance().handleEvents(ctx, _marker);
}

} // namespace Camera