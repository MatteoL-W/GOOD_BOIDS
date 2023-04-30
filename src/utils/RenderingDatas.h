#pragma once

#include <optional>
#include "Rendering/Lights/Directional.h"

namespace utils {

enum class RenderType {
    Classic,
    DepthMap
};

struct RenderingDatas {
    RenderType _renderType{};
    glm::mat4  _lightSpaceMatrix{};

    std::optional<Rendering::Lights::Directional> _directional{};
};

} // namespace utils