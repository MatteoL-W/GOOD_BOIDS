#include "Spectator.h"
#include "utils/RenderingDatas.h"

namespace Spectator {

Spectator::Spectator()
    : _controls(getControlsInstance())
{}

void Spectator::draw() const
{
    auto transformAttributes = utils::TransformAttributes{._position = getSpectatorPosition(), ._velocity = Camera::getFront()};
    auto renderingData       = utils::RenderingDatas{._renderType = utils::RenderType::Classic};

    std::visit(
        [&](auto const& shape) {
            if (!Camera::isFirstPerson())
                shape.draw(transformAttributes, renderingData);
        },
        _shape
    );
}

} // namespace Spectator