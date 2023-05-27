#pragma once

#include <p6/p6.h>
#include "utils/StrongType.h"

namespace Spectator {

struct Marker {
    glm::vec3 _front{};
    glm::vec3 _left{};
    glm::vec3 _up{};
};

class Controls {
public:
    void             handleEvents(p6::Context& ctx, Marker&, SceneRadius&);
    glm::vec3 const& getPosition() const { return _position; };
    static float     getDefaultStep() { return _step; };

private:
    static float constexpr _step = 0.05f;
    glm::vec3 _position{};
};

Controls&        getControlsInstance();
glm::vec3 const& getSpectatorPosition();

} // namespace Spectator