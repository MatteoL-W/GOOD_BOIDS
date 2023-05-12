#pragma once

#include <vector>
#include "Rendering/Engine/Model.h"

namespace utils {

class LODHandler {
public:
    /// Provide the models from the best quality to the worst
    LODHandler(std::vector<Model> models, float usedRange)
        : _models(std::move(models)), _usedRange(usedRange){};

    const Model& getCorrespondingModel(float distance) const;
    void drawCorrespondingModel(float distance) const;

private:
    std::vector<Model> _models;
    float              _usedRange;
};

} // namespace utils