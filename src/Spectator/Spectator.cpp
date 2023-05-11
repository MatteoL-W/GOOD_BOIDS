#include "Spectator.h"

void Spectator::handleEvents(p6::Context& ctx, glm::vec3 const& front, glm::vec3 const& left)
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

//void Spectator::draw()
//{
//    auto renderingData = utils::RenderingDatas{._renderType = utils::RenderType::Classic};
//    _model.draw({._position = _position}, renderingData);
//}

Spectator& getSpectatorInstance()
{
    static Spectator spectator = Spectator{};
    return spectator;
}

glm::vec3 getSpectatorPosition() {
    return getSpectatorInstance().getPosition();
}