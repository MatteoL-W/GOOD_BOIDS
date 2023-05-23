#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Intensity.h"

namespace Rendering::Lights {

class Directional {
public:
    Directional(glm::vec3 position, glm::vec3 direction, Intensity intensity, glm::vec3 color);

    glm::vec3  getPosition() const { return _position; };
    glm::vec3& getPosition() { return _position; };
    glm::vec3& getDirection() { return _direction; };
    Intensity& getIntensity() { return _intensity; };
    glm::vec3& getColor() { return _color; };

    void setMatrices(p6::Shader const&) const;

private:
    glm::vec3 _position{}; // The position is needed for the shadow
    glm::vec3 _direction{};
    Intensity _intensity{};
    glm::vec3 _color{};
};

} // namespace Rendering::Lights
