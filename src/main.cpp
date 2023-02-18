#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
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

    Boids boids{};
    int   numberOfBoids = 40;
    float boidsSize     = 0.05;
    auto  load_boids    = [&]() {
        boids = Boids{ctx, static_cast<unsigned int>(numberOfBoids), boidsSize};
    };

    ctx.imgui = [&]() {
        ImGui::Begin("Tweak values");

        ImGui::DragInt("Number of Boids", &numberOfBoids, 1.f, 0, 500);
        ImGui::DragFloat("Boids size", &boidsSize, 0.01f, 0, 2);
        if (ImGui::Button("Reload flock"))
            load_boids();

        ImGui::End();
        // mGui::ShowDemoWindow();
    };

    load_boids();

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        boids.updateAndDraw(ctx);
    };

    ctx.start();
}