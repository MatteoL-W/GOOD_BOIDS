#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace utils {

class ProjectionMatrixHandler {
public:
    void      setProjection(float aspectRatio) { _projection = glm::perspective(glm::radians(70.f), aspectRatio, .1f, 100.f); }
    glm::mat4 getProjection() const { return _projection; };

private:
    glm::mat4 _projection;
};

ProjectionMatrixHandler& getProjectionMatrixHandlerInstance();
glm::mat4 const          getProjectionMatrix();

} // namespace utils
