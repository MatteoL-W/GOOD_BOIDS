#include "Spectator.h"
#include "utils/RenderingDatas.h"

namespace Spectator {

Spectator::Spectator()
    : _controls(getControlsInstance())
{}

void Spectator::draw(utils::RenderingDatas& renderingDatas) const
{
    auto transformAttributes = utils::TransformAttributes{._position = getSpectatorPosition(), ._velocity = Camera::getFront() * glm::vec3{1.f, 0.f, 1.f}};

    std::visit(
        [&](auto const& shape) {
            if (!Camera::isFirstPerson())
                shape.draw(transformAttributes, renderingDatas);
        },
        _shape
    );
}

} // namespace Spectator