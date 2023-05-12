#pragma once

#include "p6/p6.h"

// ToDo : Remove ?

namespace Camera {

class Trackball {
public:
    Trackball(float distance = -5, float angleX = 0, float angleY = 0)
        : _distance(distance), _angleX(angleX), _angleY(angleY) {}

    // ToDo: Incorrect
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const { return glm::vec3{0.f, 0.f, 0.f}; };
    glm::mat4 getViewMatrix() const;
    void      handleEvents(p6::Context& ctx);

    void moveFront(float delta) { _distance += delta; };
    void rotateLeft(float degrees) { _angleX += degrees; };
    void rotateUp(float degrees) { _angleY += degrees; };

private:
    float _distance;
    float _angleX;
    float _angleY;

    // To Handle Events
    glm::vec3 _front{1.f, 0.f, 0.f};
    glm::vec3 _left{0.f, 0.f, -1.f};
    glm::vec3 _up{0.f, 1.f, 0.f};
};

} // namespace Camera
