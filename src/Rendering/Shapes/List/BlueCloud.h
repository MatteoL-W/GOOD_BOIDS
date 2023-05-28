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
#include "Rendering/Programs/ShadyToon/ToonAndShadow.h"
#include "utils/LODHandler.h"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class BlueCloud {
public:
    explicit BlueCloud();

    // We delete the copy constructors because the class has resources that cannot be copied
    BlueCloud(const BlueCloud& other)            = delete;
    BlueCloud& operator=(const BlueCloud& other) = delete;

    // Move constructors
    BlueCloud(BlueCloud&& other) noexcept            = default;
    BlueCloud& operator=(BlueCloud&& other) noexcept = default;

public:
    void  draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                   _radius{};
    Programs::ToonAndShadow _shader{};
    Programs::DepthMap      _depthMap{};

    utils::LODHandler _LODHandler;
};

} // namespace Rendering::Shapes