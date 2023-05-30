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

class Fence {
public:
    explicit Fence();

    // We delete the copy constructors because the class has resources that cannot be copied
    Fence(const Fence& other)            = delete;
    Fence& operator=(const Fence& other) = delete;

    // Move constructors
    Fence(Fence&& other) noexcept            = default;
    Fence& operator=(Fence&& other) noexcept = default;

    void draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;

private:
    void drawWithRightShader(glm::mat4& model, utils::RenderingDatas& renderingDatas) const;

    Programs::PhongAndShadow _shader{};
    Programs::DepthMap       _depthMap{};

    Engine::Model _model;
};

} // namespace Rendering::Shapes