#pragma once

#include <p6/p6.h>

class Spectator {
public:
    void      handleEvents(p6::Context&, glm::vec3 const& front, glm::vec3 const& left);
    glm::vec3 getPosition() const { return _position; };

private:
    void moveLeft(glm::vec3 const& left, float distance = _step) { _position += distance * left; };
    void moveRight(glm::vec3 const& left, float distance = _step) { _position -= distance * left; };
    void moveForward(glm::vec3 const& front, float distance = _step) { _position += distance * front; };
    void moveBackward(glm::vec3 const& front, float distance = _step) { _position -= distance * front; };

private:
    glm::vec3 _position{};
    static float constexpr _step = 0.1f;
};

Spectator& getSpectatorInstance();
glm::vec3  getSpectatorPosition();