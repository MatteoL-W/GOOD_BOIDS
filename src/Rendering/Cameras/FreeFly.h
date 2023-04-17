#pragma once

#include "glpp-extended/lib/glm/glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

namespace Camera {

// ToDo: Up And Down

class FreeFly {
public:
    FreeFly(glm::vec3 position = {}, float horizontalRotation = 0.f, float verticalRotation = 0.f);

    glm::mat4 getViewMatrix() const { return glm::lookAt(_position, _position + _front, _up); };
    void      handleEvents(p6::Context& ctx);

    void moveLeft(float distance) { _position -= distance * _left; };
    void moveFront(float distance) { _position += distance * _front; };
    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    void computeDirectionVectors();

private:
    glm::vec3 _position{};
    float     _horizontalRotation{p6::PI};
    float     _verticalRotation{};

    glm::vec3 _front;
    glm::vec3 _left;
    glm::vec3 _up;
};

} // namespace Camera
