#include "Controls.h"

namespace Spectator {

bool isWithinSceneBounds(const glm::vec3& position, const SceneRadius& sceneRadius)
{
    return (
        position.x >= -sceneRadius.value && position.x <= sceneRadius.value &&
        position.y >= -sceneRadius.value && position.y <= sceneRadius.value &&
        position.z >= -sceneRadius.value && position.z <= sceneRadius.value
    );
}

glm::vec3 stepUpward(float distance = Controls::getDefaultStep()) { return distance * glm::vec3{0.f, 1.f, 0.f}; };
glm::vec3 stepDownward(float distance = Controls::getDefaultStep()) { return distance * glm::vec3{0.f, -1.f, 0.f}; };
glm::vec3 stepLeft(glm::vec3 const& left, float distance = Controls::getDefaultStep()) { return distance * left; };
glm::vec3 stepRight(glm::vec3 const& left, float distance = Controls::getDefaultStep()) { return distance * left; };
glm::vec3 stepForward(glm::vec3 const& front, float distance = Controls::getDefaultStep()) { return distance * front; };
glm::vec3 stepBackward(glm::vec3 const& front, float distance = Controls::getDefaultStep()) { return distance * front; };

void Controls::handleEvents(p6::Context& ctx, Marker& marker, SceneRadius& sceneRadius)
{
    glm::vec3 newPosition = _position;

    if (ctx.key_is_pressed(GLFW_KEY_SPACE))
        newPosition += stepUpward();

    if (ctx.key_is_pressed(GLFW_KEY_TAB))
        newPosition += stepDownward();

    if (ctx.key_is_pressed(GLFW_KEY_W))
        newPosition += stepForward(marker._front);

    if (ctx.key_is_pressed(GLFW_KEY_S))
        newPosition += stepBackward(marker._front);

    if (ctx.key_is_pressed(GLFW_KEY_A))
        newPosition += stepLeft(marker._left);

    if (ctx.key_is_pressed(GLFW_KEY_D))
        newPosition += stepRight(marker._left);

    if (isWithinSceneBounds(newPosition, sceneRadius))
        _position = newPosition;
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