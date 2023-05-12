#include "Controls.h"

namespace Spectator {

void Controls::handleEvents(p6::Context& ctx, Marker& marker)
{
    ctx.key_repeated = [&](p6::Key key) {
        switch (key.physical)
        {
        case GLFW_KEY_SPACE:
            moveUpward();
            break;

        case GLFW_KEY_TAB:
            moveDownward();
            break;

        case GLFW_KEY_W:
            moveForward(marker._front);
            break;

        case GLFW_KEY_S:
            moveBackward(marker._front);
            break;

        case GLFW_KEY_A:
            moveLeft(marker._left);
            break;

        case GLFW_KEY_D:
            moveRight(marker._left);
            break;
        default:
            break;
        }
    };
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