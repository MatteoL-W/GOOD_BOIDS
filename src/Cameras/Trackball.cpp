#include "Trackball.h"

#include <glm/gtc/type_ptr.hpp>

namespace Camera {

glm::mat4 Trackball::getViewMatrix() const {
    float const angleX = _angleX * (p6::PI/180);
    float const angleY = _angleY * (p6::PI/180);

    auto view = glm::mat4{1};
    view = glm::translate(view, glm::vec3{0.f, 0.f, _distance});
    view = glm::rotate(view, angleX, glm::vec3{0.f, 1.f, 0.f}); // car on tourne sur Y
    view = glm::rotate(view, angleY, glm::vec3{-1.f, 0.f, 0.f}); // car on va vers le haut
    return view;
}

void Trackball::handleEvents(p6::Context& ctx)
{
    ctx.mouse_scrolled = [&](p6::MouseScroll scroll) {
        moveFront(scroll.dy);
    };
    ctx.mouse_dragged = [&](p6::MouseDrag drag) {
        rotateUp(drag.delta.y * 100);
        rotateLeft(drag.delta.x * 100);
    };
}

}