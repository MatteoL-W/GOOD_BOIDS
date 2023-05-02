#pragma once

#include "p6/p6.h"

namespace Camera {

class Trackball {
public:
    Trackball(float distance = -5, float angleX = 0, float angleY = 0)
        : _distance(distance), _angleX(angleX), _angleY(angleY) {}

    // ToDo: Incorrect
    glm::vec3 getPosition() const;
    glm::mat4 getViewMatrix() const;
    void      handleEvents(p6::Context& ctx);

    void moveFront(float delta) { _distance += delta; };
    void rotateLeft(float degrees) { _angleX += degrees; };
    void rotateUp(float degrees) { _angleY += degrees; };

private:
    float _distance;
    float _angleX;
    float _angleY;
};

} // namespace Camera
