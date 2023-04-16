#pragma once

#include <cstddef> // For offsetof()
#include "Rendering/Engine3D/Mesh.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/Normal.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Sphere {
public:
    explicit Sphere(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Sphere(const Sphere& other)            = delete;
    Sphere& operator=(const Sphere& other) = delete;

    // Move constructors
    Sphere(Sphere&& other) noexcept            = default;
    Sphere& operator=(Sphere&& other) noexcept = default;

public:
    void  draw(p6::Context& ctx, utils::TransformAttributes const& transformAttributes) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                                        _radius{};
    Rendering::Programs::Normal                  _shader{};
    std::vector<Rendering::Geometries::Vertex3D> _vertices{};
    RenderEngine::Mesh                           _mesh;
};

} // namespace Rendering::Shapes