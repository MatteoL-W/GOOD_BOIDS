#include "Spectator.h"
#include "utils/RenderingDatas.h"

namespace Spectator {

Spectator::Spectator()
    : _controls(getControlsInstance())
{}

void Spectator::draw(utils::RenderingDatas& renderingDatas) const
{
    auto transformAttributes = utils::TransformAttributes{
        ._position = getSpectatorPosition(),
        ._velocity = Camera::getFront(),
        ._left     = Camera::getLeft(),
    };

    std::visit(
        [&](auto const& shape) {
            if (!Camera::isFirstPerson() || renderingDatas._renderType == utils::RenderType::DepthMap)
                shape.draw(transformAttributes, renderingDatas);
        },
        _shape
    );
}

} // namespace Spectator