#include "Directional.h"

namespace Rendering::Lights {

Directional::Directional(glm::vec3 position, glm::vec3 direction, float ambient, float diffuse, float specular)
    : _position(position), _direction(direction), _ambient(ambient), _diffuse(diffuse), _specular(specular)
{}

void Directional::setMatrices(GLuint programId)
{
    _programId = programId;

    glUniform3fv(glGetUniformLocation(_programId, "dirLight.position"), 1, glm::value_ptr(_position));
    glUniform3fv(glGetUniformLocation(_programId, "dirLight.direction"), 1, glm::value_ptr(_direction));
    glUniform3fv(glGetUniformLocation(_programId, "dirLight.ambient"), 1, glm::value_ptr(glm::vec3(_ambient)));
    glUniform3fv(glGetUniformLocation(_programId, "dirLight.diffuse"), 1, glm::value_ptr(glm::vec3(_diffuse)));
    glUniform3fv(glGetUniformLocation(_programId, "dirLight.specular"), 1, glm::value_ptr(glm::vec3(_specular)));
}

} // namespace Rendering::Lights