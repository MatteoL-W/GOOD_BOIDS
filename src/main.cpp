#include <p6/p6.h>
#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <vector>
#include "Shapes/Triangle.h"

int main(int argc, char* argv[])
{
    {
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;

        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    auto ctx = p6::Context{{.title = "GOOD_BOIDS"}};
    ctx.maximize_window();

    ctx.imgui = [&]() {
        ImGui::Begin("Test");
        ImGui::End();
        // ImGui::ShowDemoWindow();
    };

    std::vector<Shapes::Triangle> triangles{};
    for (unsigned int i = 0; i < 50; i++)
    {
        triangles.emplace_back(
            glm::vec2{p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1)},
            p6::Angle{p6::Radians{p6::random::number(0, p6::TAU)}},
            0.05
        );
    }

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        for (auto& triangle : triangles)
        {
            triangle.update(ctx);
            triangle.draw(ctx);
        }
    };

    ctx.start();
}