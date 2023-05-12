#pragma once

#include <p6/p6.h>

namespace Spectator {

class Controls {
public:
    void             handleEvents(p6::Context& ctx, glm::vec3 const& up, glm::vec3 const& front, glm::vec3 const& left);
    glm::vec3 const& getPosition() const { return _position; };

private:
    void moveUpward(glm::vec3 const& up, float distance = _step) { _position += distance * up; };
    void moveDownward(glm::vec3 const& up, float distance = _step) { _position += distance * -up; };
    void moveLeft(glm::vec3 const& left, float distance = _step) { _position += distance * left; };
    void moveRight(glm::vec3 const& left, float distance = _step) { _position -= distance * left; };
    void moveForward(glm::vec3 const& front, float distance = _step) { _position += distance * front; };
    void moveBackward(glm::vec3 const& front, float distance = _step) { _position -= distance * front; };

private:
    static float constexpr _step = 0.05f;
    glm::vec3 _position{};
};

Controls&        getControlsInstance();
glm::vec3 const& getSpectatorPosition();

} // namespace Spectator