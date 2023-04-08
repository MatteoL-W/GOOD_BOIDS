#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include "Program/Normal.h"
#include "Utils/Mesh.h"
#include "Utils/TransformAttributes.h"
#include "Utils/geometriesVertices.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Shapes::ThreeDimensions {

class Cone {
public:
    explicit Cone(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Cone(const Cone& other)            = delete;
    Cone& operator=(const Cone& other) = delete;

    // Move constructors
    Cone(Cone&& other) noexcept = default;
    Cone& operator=(Cone&& other) noexcept = default;

public:
    void  draw(p6::Context& ctx, Utils::TransformAttributes const& transformAttributes) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                        _radius{};
    Program::Normal              _shader{};
    std::vector<Utils::Vertex3D> _vertices{};
    RenderEngine::Mesh           _mesh;
};

} // namespace Shapes::ThreeDimensions