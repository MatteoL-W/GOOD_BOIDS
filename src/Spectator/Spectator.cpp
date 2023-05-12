#include "Spectator.h"
#include "utils/RenderingDatas.h"

namespace Spectator {

Spectator::Spectator()
    : _controls(getControlsInstance())
{}

void Spectator::draw(utils::RenderingDatas& renderingDatas) const
{
    auto directionForProdCameras = Camera::getFront() * glm::vec3{1.f, 0.f, 1.f}; // Prod cameras = Third and First person camera
    auto directionForAllCameras = (directionForProdCameras) == glm::vec3{0.f} ? glm::vec3{1.f, 0.f, 0.f} : directionForProdCameras;
    auto transformAttributes = utils::TransformAttributes{._position = getSpectatorPosition(), ._velocity = directionForAllCameras};

    std::visit(
        [&](auto const& shape) {
            if (!Camera::isFirstPerson() || renderingDatas._renderType == utils::RenderType::DepthMap)
                shape.draw(transformAttributes, renderingDatas);
        },
        _shape
    );
}

} // namespace Spectator