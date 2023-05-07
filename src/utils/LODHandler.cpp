#include "LODHandler.h"

namespace utils {

const Model& LODHandler::getCorrespondingModel(float distance) const
{
    if (_models.empty())
        exit(1);

    for (size_t i = 0; i < _models.size() - 1; i++)
        if (distance < (_usedRange / _models.size()) * (i+1))
            return _models[i];

    return _models[_models.size()-1];
}

void LODHandler::drawCorrespondingModel(float distance) const
{
    getCorrespondingModel(distance).draw();
}

} // namespace utils