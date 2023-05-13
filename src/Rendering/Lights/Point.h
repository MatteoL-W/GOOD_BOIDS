#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>
#include "Intensity.h"

namespace Rendering::Lights {

class Point {
public:
    Point(glm::vec3 position, Intensity intensity, float constant, float linear, float quadratic);

    glm::vec3& getPosition() { return _position; };
    Intensity& getIntensity() { return _intensity; };
    float& getConstant() { return _constant; };
    float& getLinear() { return _linear; };
    float& getQuadratic() { return _quadratic; };

    void setMatrices(unsigned int index, p6::Shader const&) const;
    void setPosition(glm::vec3 position) { _position = position; };

private:
    // ToDo: Color
    glm::vec3 _position{};
    Intensity _intensity{};

    float _constant{};
    float _linear{};
    float _quadratic{};
};

} // namespace Rendering::Lights
