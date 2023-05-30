#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap/DepthMap.h"
#include "Rendering/Programs/ShadyPhong/PhongAndShadow.h"
#include "utils/LODHandler.h"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class House {
public:
    explicit House();

    // We delete the copy constructors because the class has resources that cannot be copied
    House(const House& other)            = delete;
    House& operator=(const House& other) = delete;

    // Move constructors
    House(House&& other) noexcept            = default;
    House& operator=(House&& other) noexcept = default;

    void draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;

private:
    Programs::PhongAndShadow _shader{};
    Programs::DepthMap       _depthMap{};

    Engine::Model _model;
};

} // namespace Rendering::Shapes