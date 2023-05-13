#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap/DepthMap.h"
#include "Rendering/Programs/ShadyPhong/PhongAndShadow.h"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Cone {
public:
    explicit Cone(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Cone(const Cone& other)            = delete;
    Cone& operator=(const Cone& other) = delete;

    // Move constructors
    Cone(Cone&& other) noexcept            = default;
    Cone& operator=(Cone&& other) noexcept = default;

public:
    void  draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                             _radius{};
    Programs::PhongAndShadow          _shader{};
    Programs::DepthMap                _depthMap{};
    std::vector<Geometries::Vertex3D> _vertices{};
    Engine::Mesh                      _mesh;
};

} // namespace Rendering::Shapes