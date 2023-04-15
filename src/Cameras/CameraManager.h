#pragma once

#include <variant>
#include "FreeFly.h"
#include "Trackball.h"

namespace Camera {

using CameraType = std::variant<FreeFly, Trackball>;

class CameraManager {
public:
    explicit CameraManager(CameraType&);

    glm::mat4 getViewMatrix() const;
    void      handleEvents(p6::Context& ctx);
    void      changeCamera(CameraType& newCamera);

private:
    CameraType& _camera;
};

CameraManager const& getCameraInstance();

} // namespace Camera
