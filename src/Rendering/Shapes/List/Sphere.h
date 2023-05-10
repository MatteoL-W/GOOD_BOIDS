#pragma once

// ToDo: Delete

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/DepthMap/DepthMap.h"
#include "Rendering/Programs/Normal/Normal.h"
#include "utils/RenderingDatas.h"
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
    void  draw(utils::TransformAttributes const& transformAttributes, utils::RenderingDatas&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                                        _radius{};
    Rendering::Programs::Normal                  _shader{};
    std::vector<Rendering::Geometries::Vertex3D> _vertices{};
    Rendering::Engine::Mesh                      _mesh;
};

} // namespace Rendering::Shapes