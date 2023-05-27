#pragma once

#include <variant>
#include "FirstPerson.h"
#include "ThirdPerson.h"
#include "Trackball.h"

namespace Camera {

using CameraType = std::variant<Trackball, ThirdPerson, FirstPerson>;

class CameraManager {
public:
    explicit CameraManager(CameraType&);

    glm::vec3  getPosition() const;
    glm::vec3  getFront() const;
    glm::vec3  getLeft() const;
    glm::mat4  getViewMatrix() const;
    CameraType getAbstractCamera() const { return _camera; };
    void       handleEvents(p6::Context& ctx);
    void       updateEvents(p6::Context& ctx);
    void       changeCamera(CameraType& newCamera);

private:
    CameraType& _camera;
};

CameraManager const& getCameraInstance();

bool      isFirstPerson();
glm::mat4 getViewMatrix();
glm::vec3 getPosition();
glm::vec3 getFront();
glm::vec3 getLeft();

} // namespace Camera
