#pragma once

#include <p6/p6.h>

namespace Rendering::Engine {

class Texture {
public:
    Texture(int width, int height, uint8_t const* data);
    explicit Texture(std::string imagePath);

    // We delete the copy constructors because the class has resources that cannot be copied
    Texture(const Texture& other)            = delete;
    Texture& operator=(const Texture& other) = delete;

    // Move constructors
    Texture(Texture&& other) noexcept            = default;
    Texture& operator=(Texture&& other) noexcept = default;

    ~Texture();

public:
    void        bindOnUnit(GLuint unitId) const;
    static void unbind();

private:
    GLuint _id{};
};

} // namespace Rendering::Engine
