#include "ProjectionMatrixHandler.h"

namespace utils {

ProjectionMatrixHandler& getProjectionMatrixHandlerInstance()
{
    static auto handler = ProjectionMatrixHandler{};
    return handler;
}

glm::mat4 const getProjectionMatrix()
{
    const auto handler = getProjectionMatrixHandlerInstance();
    return handler.getProjection();
}

} // namespace utils
