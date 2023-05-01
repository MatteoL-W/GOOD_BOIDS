#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>

namespace Rendering::Lights {

class Point {
public:
    Point(glm::vec3 position, float constant, float linear, float quadratic, float ambient, float diffuse, float specular);
    void setMatrices(unsigned int index, p6::Shader const&) const;

private:
    glm::vec3 _position{};

    float _constant{};
    float _linear{};
    float _quadratic{};

    // Intensities
    float _ambient{};
    float _diffuse{};
    float _specular{};
};

} // namespace Rendering::Lights
