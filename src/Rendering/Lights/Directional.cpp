#include "Directional.h"

namespace Rendering::Lights {

Directional::Directional(glm::vec3 position, glm::vec3 direction, float ambient, float diffuse, float specular)
    : _position(position), _direction(direction), _ambient(ambient), _diffuse(diffuse), _specular(specular)
{}

void Directional::setMatrices(p6::Shader const& program) const
{
    program.set("dirLight.position", _position);
    program.set("dirLight.direction", _direction);
    program.set("dirLight.ambient", glm::vec3(_ambient));
    program.set("dirLight.diffuse", glm::vec3(_diffuse));
    program.set("dirLight.specular", glm::vec3(_specular));
}

} // namespace Rendering::Lights