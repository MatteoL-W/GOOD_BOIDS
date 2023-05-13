#pragma once

#include <vector>
#include "Rendering/Engine/Model.h"

namespace utils {

class LODHandler {
public:
    /// Provide the models from the best quality to the worst
    LODHandler(std::vector<Rendering::Engine::Model> models, float usedRange)
        : _models(std::move(models)), _usedRange(usedRange){};

    void drawCorrespondingModel(glm::vec3 position) const;

private:
    std::vector<Rendering::Engine::Model> _models;
    float              _usedRange;
};

} // namespace utils