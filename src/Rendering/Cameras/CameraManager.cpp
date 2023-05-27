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

glm::vec3 CameraManager::getFront() const
{
    auto front = glm::vec3{};
    std::visit(
        [&](auto const& camera) {
            front = camera.getFront();
        },
        _camera
    );
    return front;
}

glm::vec3 CameraManager::getLeft() const
{
    auto left = glm::vec3{};
    std::visit(
        [&](auto const& camera) {
            left = camera.getLeft();
        },
        _camera
    );
    return left;
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

void CameraManager::updateEvents(p6::Context& ctx)
{
    std::visit(
        [&](auto& camera) {
            camera.updateEvents(ctx);
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

bool isFirstPerson()
{
    auto camera = getCameraInstance();
    return std::holds_alternative<FirstPerson>(camera.getAbstractCamera());
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

glm::vec3 getFront()
{
    auto camera = getCameraInstance();
    return camera.getFront();
}

glm::vec3 getLeft()
{
    auto camera = getCameraInstance();
    return camera.getLeft();
}

} // namespace Camera