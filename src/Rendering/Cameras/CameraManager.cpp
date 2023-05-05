#include "CameraManager.h"

namespace Camera {

CameraManager::CameraManager(CameraType& camera)
    : _camera(camera)
{}

glm::vec3 CameraManager::getPosition() const
{
    auto position = glm::vec3{};
    std::visit(
        [&](auto const& camera) {
            position = camera.getPosition();
        },
        _camera
    );
    return position;
}

glm::mat4 CameraManager::getViewMatrix() const
{
    auto viewMatrix = glm::mat4{};
    std::visit(
        [&](auto const& camera) {
            viewMatrix = camera.getViewMatrix();
        },
        _camera
    );
    return viewMatrix;
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
    static Camera::CameraType  defaultCamera = Camera::ThirdPerson{};
    static CameraManager const cameraManager = CameraManager{defaultCamera};
    return cameraManager;
}

glm::mat4 getViewMatrix()
{
    auto camera = getCameraInstance();
    return camera.getViewMatrix();
}

glm::vec3 getPosition()
{
    auto camera = getCameraInstance();
    return camera.getPosition();
}

} // namespace Camera