#pragma once

#include <p6/p6.h>
#include <glpp-extended/lib/glm/glm/gtc/type_ptr.hpp>

namespace Rendering::Lights {

class Directional {
public:
    Directional(glm::vec3 position, glm::vec3 direction, float ambient, float diffuse, float specular);
    void setMatrices(GLuint programId);

private:
    GLuint _programId{};

    glm::vec3 _position{}; // The position is needed for the shadow
    glm::vec3 _direction{};

    // Intensities
    float _ambient{};
    float _diffuse{};
    float _specular{};
};

} // namespace Rendering::Lights
