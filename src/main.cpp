#include <p6/p6.h>
#include <cstdlib>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include "Boids.h"

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
    ctx.framerate_capped_at(60); // Avoid differents results on 240Hz/60Hz

    ctx.imgui = [&]() {
        ImGui::Begin("Test");
        ImGui::End();
        // ImGui::ShowDemoWindow();
    };

    auto boids = Boids{ctx, 20};

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        boids.updateAndDraw(ctx);
    };

    ctx.start();
}