#pragma once

#include <optional>
#include <vector>
#include "Rendering/Lights/Directional.h"
#include "Rendering/Lights/Point.h"

namespace utils {

enum class RenderType {
    Classic,
    DepthMap
};

struct RenderingDatas {
    RenderType _renderType{};

    // Needed for shadows
    glm::mat4  _lightSpaceMatrix{};

    // Lights
    std::optional<Rendering::Lights::Directional> _directional{};
    std::vector<Rendering::Lights::Point>         _points{};
};

} // namespace utils