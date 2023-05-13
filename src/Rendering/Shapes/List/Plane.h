#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap/DepthMap.h"
#include "Rendering/Programs/ShadyPhong/PhongAndShadow.h"
#include "Rendering/Programs/Texture/Texture.h"
#include "glm/ext/vector_float3.hpp"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Plane {
public:
    explicit Plane(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Plane(const Plane& other)            = delete;
    Plane& operator=(const Plane& other) = delete;

    // Move constructors
    Plane(Plane&& other) noexcept            = default;
    Plane& operator=(Plane&& other) noexcept = default;

public:
    void  draw([[maybe_unused]] utils::TransformAttributes const&, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    GLuint                            _textureId{};
    float                             _radius{};
    Programs::PhongAndShadow          _shader{};
    Programs::DepthMap                _depthMap{};
    std::vector<Geometries::Vertex3D> _vertices{};
    Engine::Mesh                      _mesh;
};

} // namespace Rendering::Shapes