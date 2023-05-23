#pragma once

#include <p6/p6.h>
#include "Rendering/Programs/SkyBox/SkyBox.h"

namespace Rendering::Engine {

class SkyBox {
public:
    SkyBox();
    ~SkyBox();

    // We delete the copy constructors because the class has resources that cannot be copied
    SkyBox(const SkyBox& other)            = delete;
    SkyBox& operator=(const SkyBox& other) = delete;

    // Move constructors
    SkyBox(SkyBox&& other) noexcept            = default;
    SkyBox& operator=(SkyBox&& other) noexcept = default;

    void draw();

private:
    void createTexture(std::vector<std::string> faces);
    void createMesh();

private:
    Programs::SkyBox _skyBoxShader{};
    GLuint           _cubeMapTextureId{};
    GLuint           _vbo{};
    GLuint           _vao{};
};

} // namespace Rendering::Engine
