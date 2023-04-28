#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap.h"
#include "Rendering/Programs/PhongAndShadow.h"
#include "Rendering/Programs/Texture.h"
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
    void  draw(utils::TransformAttributes const& transformAttributes, glm::mat4 lightSpaceMatrix) const;
    void  drawDepthMap(utils::TransformAttributes const&, glm::mat4 lightSpaceMatrix) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    GLuint                                       textureId{};
    float                                        _radius{};
    Rendering::Programs::PhongAndShadow          _shader{};
    Rendering::Programs::DepthMap                _depthMap{};
    std::vector<Rendering::Geometries::Vertex3D> _vertices{};
    RenderEngine::Mesh                           _mesh;
};

} // namespace Rendering::Shapes