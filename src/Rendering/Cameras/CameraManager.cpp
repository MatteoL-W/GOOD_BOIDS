#include "CameraManager.h"

namespace Camera {

CameraManager::CameraManager(CameraType& camera)
    : _camera(camera)
{}

glm::mat4 CameraManager::getViewMatrix() const
{
    auto _viewMatrix = glm::mat4{};
    std::visit(
        [&](auto const& camera) {
            _viewMatrix = camera.getViewMatrix();
        },
        _camera
    );
    return _viewMatrix;
}

void CameraManager::handleEvents(p6::Context& ctx)
{
    std::visit(
        [&](auto& camera) {
            camera.handleEvents(ctx);
        },
        _camera
    );
}

void CameraManager::changeCamera(CameraType& newCamera)
{
    _camera = newCamera;
}

CameraManager const& getCameraInstance()
{
    static Camera::CameraType  defaultCamera = Camera::Trackball{};
    static CameraManager const cameraManager = CameraManager{defaultCamera};
    return cameraManager;
}

glm::mat4 getViewMatrix()
{
    auto camera = getCameraInstance();
    return camera.getViewMatrix();
}

} // namespace Camera