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
    ctx.framerate_capped_at(60); // Avoid different results on 240Hz/60Hz

    auto config = Config{
        ._radius = 0.02f,
        ._maxSpeed = 2.f,
        ._separation_radius = 0.1f,
        ._alignment_radius = 0.2f,
        ._cohesion_radius = 0.1f,
    };

    Boids boids{};
    int   numberOfBoids = 300;
    auto  load_boids    = [&]() {
        boids = Boids{ctx, static_cast<unsigned int>(numberOfBoids), config};
    };
    load_boids();

    ctx.imgui = [&]() {
        ImGui::Begin("Tweak values");

        ImGui::DragInt("Number of Boids", &numberOfBoids, 1.f, 0, 500);
        ImGui::DragFloat("Boids size", &config._radius, 0.01f, 0.f, 2.f);
        ImGui::DragFloat("Boids max speed", &config._maxSpeed, 0.01f, 0.f, 5.f);
        ImGui::DragFloat("Boids separation radius", &config._separation_radius, 0.01f, 0, 1.f);
        ImGui::DragFloat("Boids alignment radius", &config._alignment_radius, 0.01f, 0, 1.f);
        ImGui::DragFloat("Boids cohesion radius", &config._cohesion_radius, 0.01f, 0, 1.f);

        if (ImGui::Button("Reload flock"))
            load_boids();

        ImGui::End();
        // mGui::ShowDemoWindow();
    };

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        boids.updateAndDraw(ctx);
    };

    ctx.start();
}