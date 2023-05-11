#pragma once

#include <variant>
#include "FreeFly.h"
#include "ThirdPerson.h"
#include "FirstPerson.h"
#include "Trackball.h"

namespace Camera {

using CameraType = std::variant<FreeFly, Trackball, ThirdPerson, FirstPerson>;

class CameraManager {
public:
    explicit CameraManager(CameraType&);

    glm::vec3 getPosition() const;
    glm::mat4 getViewMatrix() const;
    void      handleEvents(p6::Context& ctx);
    void      changeCamera(CameraType& newCamera);

private:
    CameraType& _camera;
};

CameraManager const& getCameraInstance();
glm::mat4            getViewMatrix();
glm::vec3            getPosition();

} // namespace Camera
