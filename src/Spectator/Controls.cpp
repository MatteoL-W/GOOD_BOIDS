#include "Controls.h"

namespace Spectator {

void Controls::handleEvents(p6::Context& ctx, glm::vec3 const& front, glm::vec3 const& left)
{
    ctx.key_repeated = [&](p6::Key key) {
        switch (key.physical)
        {
        case GLFW_KEY_W:
            moveForward(front);
            break;

        case GLFW_KEY_S:
            moveBackward(front);
            break;

        case GLFW_KEY_A:
            moveLeft(left);
            break;

        case GLFW_KEY_D:
            moveRight(left);
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

glm::vec3 getSpectatorPosition()
{
    return getControlsInstance().getPosition();
}

} // namespace Spectator