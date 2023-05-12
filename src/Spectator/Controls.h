#pragma once

#include <p6/p6.h>

namespace Spectator {

struct Marker {
    glm::vec3 _front{};
    glm::vec3 _left{};
    glm::vec3 _up{};
};

class Controls {
public:
    void             handleEvents(p6::Context& ctx, Marker&);
    glm::vec3 const& getPosition() const { return _position; };

private:
    void moveUpward(float distance = _step) { _position += distance * glm::vec3{0.f, 1.f, 0.f}; };
    void moveDownward(float distance = _step) { _position += distance * glm::vec3{0.f, -1.f, 0.f}; };
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