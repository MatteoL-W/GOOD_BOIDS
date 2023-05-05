#include "LODHandler.h"

namespace utils {

void LODHandler::drawCorrespondingModel(glm::vec3 position) const
{
    float distance = glm::distance(position, Camera::getPosition());
    if (_models.empty())
        return;

    for (size_t i = 0; i < _models.size() - 1; i++)
        if (distance < (_usedRange / _models.size()) * (i+1))
        {
            _models[i].draw();
            return;
        }

    // Draw the last model if we're out of range
    _models[_models.size()-1].draw();
}

} // namespace utils