#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Engine/Texture.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap/DepthMap.h"
#include "Rendering/Programs/ShadyPhong/PhongAndShadow.h"
#include "Rendering/Programs/Texture/Texture.h"
#include "glm/ext/vector_float3.hpp"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Ground {
public:
    explicit Ground(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Ground(const Ground& other)            = delete;
    Ground& operator=(const Ground& other) = delete;

    // Move constructors
    Ground(Ground&& other) noexcept            = default;
    Ground& operator=(Ground&& other) noexcept = default;

public:
    void  draw([[maybe_unused]] utils::TransformAttributes const&, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    Engine::Texture                   _texture;
    float                             _radius{};
    Programs::PhongAndShadow          _shader{};
    std::vector<Geometries::Vertex3D> _vertices{};
    Engine::Mesh                      _mesh;
};

} // namespace Rendering::Shapes