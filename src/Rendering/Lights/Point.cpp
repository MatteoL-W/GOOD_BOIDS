#include "Point.h"

namespace Rendering::Lights {

Point::Point(glm::vec3 position, float constant, float linear, float quadratic, float ambient, float diffuse, float specular)
    : _position(position), _constant(constant), _linear(linear), _quadratic(quadratic), _ambient(ambient), _diffuse(diffuse), _specular(specular)
{}

void Point::setMatrices(unsigned int index, GLuint programId)
{
    auto prefix = std::string("pointLights[" + std::to_string(index) + "].");
    auto addPrefix = [prefix](const char* property) { return prefix + property; };

    glUniform3fv(glGetUniformLocation(programId, addPrefix("position").c_str()), 1, glm::value_ptr(_position));
    glUniform1f(glGetUniformLocation(programId, addPrefix("constant").c_str()), _constant);
    glUniform1f(glGetUniformLocation(programId, addPrefix("linear").c_str()), _linear);
    glUniform1f(glGetUniformLocation(programId, addPrefix("quadratic").c_str()), _quadratic);
    glUniform3fv(glGetUniformLocation(programId, addPrefix("ambient").c_str()), 1, glm::value_ptr(glm::vec3(_ambient)));
    glUniform3fv(glGetUniformLocation(programId, addPrefix("diffuse").c_str()), 1, glm::value_ptr(glm::vec3(_diffuse)));
    glUniform3fv(glGetUniformLocation(programId, addPrefix("specular").c_str()), 1, glm::value_ptr(glm::vec3(_specular)));
}

} // namespace Rendering::Lights