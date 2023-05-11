#include "Spectator.h"
#include "utils/RenderingDatas.h"

namespace Spectator {

Spectator::Spectator()
    : _controls(getControlsInstance())
{}

void Spectator::draw() const
{
    auto renderingData = utils::RenderingDatas{._renderType = utils::RenderType::Classic};

    std::visit(
        [&](auto const& shape) {
            if (!Camera::isFirstPerson())
                shape.draw({._position = getSpectatorPosition()}, renderingData);
        },
        _shape
    );
}

} // namespace Spectator