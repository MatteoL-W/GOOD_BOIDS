#pragma once

#include "Spectator/Controls.h"
#include "glpp-extended/lib/glm/glm/gtc/matrix_transform.hpp"
#include "p6/p6.h"

namespace Camera {

class FirstPerson {
public:
    explicit FirstPerson();

    glm::vec3 getPosition() const { return Spectator::getSpectatorPosition(); };
    glm::vec3 getFront() const { return _marker._front; };
    glm::vec3 getLeft() const { return _marker._left; };
    glm::mat4 getViewMatrix() const { return glm::lookAt(getPosition(), getPosition() + _marker._front, _marker._up); };

    void setMarker(Spectator::Marker& marker) { _marker = marker; };

    void handleEvents(p6::Context& ctx);
    void updateEvents(p6::Context& ctx, SceneRadius& sceneRadius) { Spectator::getControlsInstance().handleEvents(ctx, _marker, sceneRadius); };

    void rotateLeft(float degrees);
    void rotateUp(float degrees);

private:
    void computeDirectionVectors();

private:
    Spectator::Marker _marker{};

    float _horizontalRotation{p6::PI};
    float _verticalRotation{};
};

} // namespace Camera
