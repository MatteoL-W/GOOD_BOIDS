#pragma once

#include <p6/p6.h>

namespace Program {

struct Texture {
    p6::Shader _program;

    GLint uMVPMatrix{};
    GLint uMVMatrix{};
    GLint uNormalMatrix{};

    Texture()
        : _program{p6::load_shader("../src/Program/Shaders/3D.vs.glsl", "../src/Program/Shaders/texture.fs.glsl")}
        , uMVPMatrix(glGetUniformLocation(_program.id(), "uMVPMatrix"))
        , uMVMatrix(glGetUniformLocation(_program.id(), "uMVMatrix"))
        , uNormalMatrix(glGetUniformLocation(_program.id(), "uNormalMatrix"))
    {}
};

} // namespace Program