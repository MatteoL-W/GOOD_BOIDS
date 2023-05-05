#pragma once

#include "Spectator/Spectator.h"
#include "glpp-extended/lib/glm/glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

namespace Camera {

class ThirdPerson {
public:
    explicit ThirdPerson();

    glm::vec3 getPosition() const { return _spectator.getPosition(); };
    glm::mat4 getViewMatrix() const { return glm::lookAt(getPosition(), getPosition() + _front, _up); };
    void      handleEvents(p6::Context& ctx);

    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    void computeDirectionVectors();

private:
    Spectator _spectator{};

    glm::vec3 _front{};
    glm::vec3 _left{};
    glm::vec3 _up{};

    float     _horizontalRotation{p6::PI};
    float     _verticalRotation{};
};

} // namespace Camera
