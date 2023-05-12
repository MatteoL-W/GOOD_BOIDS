#pragma once

#include "Spectator/Controls.h"
#include "glpp-extended/lib/glm/glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

namespace Camera {

class ThirdPerson {
public:
    explicit ThirdPerson();

    glm::vec3 getPosition() const { return Spectator::getSpectatorPosition() - _distanceToXPos * glm::normalize(_marker._front) + _marker._up; };
    glm::vec3 getFront() const { return _marker._front; };
    glm::mat4 getViewMatrix() const { return glm::lookAt(getPosition(), getPosition() + _marker._front, _marker._up); };
    void      handleEvents(p6::Context& ctx);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    void computeDirectionVectors();

private:
    static float constexpr _distanceToXPos = 3.f;

    Spectator::Marker _marker{};

    float _horizontalRotation{p6::PI};
    float _verticalRotation{};
};

} // namespace Camera
