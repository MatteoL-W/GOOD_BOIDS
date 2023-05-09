#include "AnimatedCube.h"
#include "Rendering/Engine/Mesh.h"

namespace Rendering::Shapes {

AnimatedCube::AnimatedCube()
    : _model(Model{"assets/models/AnimatedCube/AnimatedCube.gltf"})
{}

void AnimatedCube::update(float currentTime)
{
    _model.playAllAnimations(currentTime);
}

void AnimatedCube::draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas& renderingDatas) const
{
    // Two lines per variables to handle the cast from vector<double> to vec3<float>
    std::vector<double> rotationVec = _model.getModel().nodes[0].rotation;
    glm::quat rotation = (rotationVec.size() >= 4) ? glm::make_quat(glm::value_ptr(glm::dquat(rotationVec[3], rotationVec[0], rotationVec[1], rotationVec[2]))) : glm::dquat();

    std::vector<double> scaleVec = _model.getModel().nodes[0].scale;
    glm::vec3 scale = scaleVec.empty() ? glm::vec3(1.0f) : glm::vec3(scaleVec[0], scaleVec[1], scaleVec[2]);

    std::vector<double> translationVec = _model.getModel().nodes[0].translation;
    glm::vec3 translation = translationVec.empty() ? glm::vec3(0.0f) : glm::vec3(translationVec[0], translationVec[1], translationVec[2]);

    auto modelMatrix = glm::mat4_cast(rotation) *
                       glm::translate(glm::mat4{1}, translation) *
                       glm::scale(glm::mat4{1}, scale) *
                       glm::translate(glm::mat4{1}, transformAttributes._position);

    switch (renderingDatas._renderType)
    {
    case utils::RenderType::Classic:
        _shader._program.use();
        _shader.setMatrices(modelMatrix, renderingDatas);
        break;

    case utils::RenderType::DepthMap:
        _depthMap._program.use();
        _depthMap.setMatrices(modelMatrix, renderingDatas._lightSpaceMatrix);
        break;
    }

    _model.draw();

    glUseProgram(0);
}

} // namespace Rendering::Shapes