#pragma once

#include "Spectator/Controls.h"
#include "p6/p6.h"

// Only Debug use

namespace Camera {

class Trackball {
public:
    explicit Trackball(float distance = -5, float angleX = 0, float angleY = 0)
        : _distance(distance), _angleX(angleX), _angleY(angleY) {}

    glm::vec3 getPosition() const;
    glm::vec3 getFront() const { return glm::vec3{1.f, 0.f, 0.f}; };
    glm::mat4 getViewMatrix() const;
    void      handleEvents(p6::Context& ctx);
    void      updateEvents(p6::Context& ctx) { Spectator::getControlsInstance().handleEvents(ctx, _marker); };

    void moveFront(float delta) { _distance += delta; };
    void rotateLeft(float degrees) { _angleX += degrees; };
    void rotateUp(float degrees) { _angleY += degrees; };

private:
    float _distance;
    float _angleX;
    float _angleY;

    // To Handle Events
    Spectator::Marker _marker{
        ._front{1.f, 0.f, 0.f},
        ._left{0.f, 0.f, -1.f},
        ._up{0.f, 1.f, 0.f}};
};

} // namespace Camera
