#pragma once

#include "Controls.h"
#include "Rendering/Shapes/ShapesRegister.h"

namespace Spectator {

class Spectator {
public:
    Spectator();
    void draw() const;

private:
    Controls _controls;

    SpectatorShapesType const& _shape{Rendering::Shapes::getDuckInstance2()};
};

} // namespace Spectator
