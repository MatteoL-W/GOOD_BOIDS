#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Rendering/Engine/Mesh.h"
#include "Rendering/Engine/Model.h"
#include "Rendering/Geometries/geometriesVertices.hpp"
#include "Rendering/Programs/Transparent/Transparent.h"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Rendering::Shapes {

class Cube {
public:
    explicit Cube(float radius);

    // We delete the copy constructors because the class has resources that cannot be copied
    Cube(const Cube& other)            = delete;
    Cube& operator=(const Cube& other) = delete;

    // Move constructors
    Cube(Cube&& other) noexcept            = default;
    Cube& operator=(Cube&& other) noexcept = default;

public:
    void  draw() const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float                            _radius{};
    Rendering::Programs::Transparent _shader{};
    Model                            _model;
};

} // namespace Rendering::Shapes