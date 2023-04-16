#pragma once

#include <cstddef> // For offsetof()
#include "Rendering/Engine3D/Mesh.h"
#include "Rendering/Engine3D/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/Normal.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "p6/p6.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Duck {
public:
    explicit Duck();

    // We delete the copy constructors because the class has resources that cannot be copied
    Duck(const Duck& other)            = delete;
    Duck& operator=(const Duck& other) = delete;

    // Move constructors
    Duck(Duck&& other) noexcept            = default;
    Duck& operator=(Duck&& other) noexcept = default;

public:
    void  draw(p6::Context&, utils::TransformAttributes const&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                        _radius{};
    Rendering::Programs::Texture _shader{};
    Model                        _model;
};

} // namespace Rendering::Shapes