#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/Texture.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Plane {
public:
    explicit Plane(float radius);
    explicit Plane(float radius, std::vector<Rendering::Geometries::Vertex3D> vertices);

    // We delete the copy constructors because the class has resources that cannot be copied
    Plane(const Plane& other)            = delete;
    Plane& operator=(const Plane& other) = delete;

    // Move constructors
    Plane(Plane&& other) noexcept            = default;
    Plane& operator=(Plane&& other) noexcept = default;

public:
    void  draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                                        _radius{};
    Rendering::Programs::Texture                 _shader{};
    std::vector<Rendering::Geometries::Vertex3D> _vertices{};
    RenderEngine::Mesh                           _mesh;
};

} // namespace Rendering::Shapes