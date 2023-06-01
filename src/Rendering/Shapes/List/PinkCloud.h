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

class PinkCloud {
public:
    explicit PinkCloud();

    // We delete the copy constructors because the class has resources that cannot be copied
    PinkCloud(const PinkCloud& other)            = delete;
    PinkCloud& operator=(const PinkCloud& other) = delete;

    // Move constructors
    PinkCloud(PinkCloud&& other) noexcept            = default;
    PinkCloud& operator=(PinkCloud&& other) noexcept = default;

public:
    void  draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                   _radius{0.2f};
    Programs::PhongAndShadow _shader{};
    Programs::DepthMap      _depthMap{};

    utils::LODHandler _LODHandler;
};

} // namespace Rendering::Shapes