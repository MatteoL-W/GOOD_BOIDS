#include "Controls.h"

namespace Spectator {

void Controls::handleEvents(p6::Context& ctx, Marker& marker)
{
    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
        moveUpward();

    if (ctx.key_is_pressed(GLFW_KEY_TAB))
        moveDownward();

    if (ctx.key_is_pressed(GLFW_KEY_W))
        moveForward(marker._front);

    if (ctx.key_is_pressed(GLFW_KEY_S))
        moveBackward(marker._front);

    if (ctx.key_is_pressed(GLFW_KEY_A))
        moveLeft(marker._left);

    if (ctx.key_is_pressed(GLFW_KEY_D))
        moveRight(marker._left);
}

Controls& getControlsInstance()
{
    static Controls spectator = Controls{};
    return spectator;
}

glm::vec3 const& getSpectatorPosition()
{
    return getControlsInstance().getPosition();
}

} // namespace Spectator