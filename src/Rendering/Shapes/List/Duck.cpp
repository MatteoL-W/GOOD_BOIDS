#include "Duck.h"
#include "Cameras/CameraManager.h"
#include "Rendering/Engine3D/Mesh.h"

namespace Rendering::Shapes {

Duck::Duck()
    : _model("assets/models/Duck/Duck.gltf")
{}

void Duck::draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes) const
{
    _shader._program.use();
    auto cameraManager = Camera::getCameraInstance();

    auto modelViewMatrix = cameraManager.getViewMatrix();
    modelViewMatrix      = glm::translate(modelViewMatrix, transformAttributes._position);
    modelViewMatrix      = glm::scale(modelViewMatrix, glm::vec3(0.01f));

    auto projectionMatrix = glm::perspective(glm::radians(70.f), ctx.aspect_ratio(), .1f, 100.f);
    auto normalMatrix     = glm::transpose(glm::inverse(modelViewMatrix));

    glUniformMatrix4fv(_shader.uMVMatrix, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(_shader.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix * modelViewMatrix));
    glUniformMatrix4fv(_shader.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(normalMatrix));

    _model.draw();
}

} // namespace Rendering::Shapes