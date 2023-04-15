#pragma once

#include <p6/p6.h>
#include <cstddef> // For offsetof()
#include "Program/Normal.h"
#include "Utils/Mesh.h"
#include "Utils/Model.h"
#include "Utils/TransformAttributes.h"
#include "Utils/geometriesVertices.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace Shapes::ThreeDimensions {

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
    void  draw(p6::Context&, Utils::TransformAttributes const&) const;
    void  setRadius(float radius) { _radius = radius; };
    float getRadius() const { return _radius; };

private:
    float            _radius{};
    Program::Texture _shader{};
    Model            _model;
};

} // namespace Shapes::ThreeDimensions