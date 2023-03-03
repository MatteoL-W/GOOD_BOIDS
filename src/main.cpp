#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids.h"
#include "Obstacles.h"
#include "Shapes/2D.h"

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

    float      radius = .02f;
    ShapesType shape  = Shapes::TwoDimensions::Fish{radius};

    auto behaviorConfig = BehaviorConfig{
        ._maxSpeed = 1.f,
    };

    auto forcesConfig = ForcesConfig{
        ._separation_radius = 0.1f,
        ._alignment_radius  = 0.23f,
        ._cohesion_radius   = 0.1f,
    };

    Boids boids{};
    int   numberOfBoids = 50;
    auto  load_boids    = [&]() {
        boids = Boids{ctx, static_cast<unsigned int>(numberOfBoids), shape, behaviorConfig, forcesConfig};
    };
    load_boids();

    ctx.imgui = [&]() {
        ImGui::Begin("Tweak values");

        ImGui::DragInt("Number of Boids", &numberOfBoids, 1.f, 0, 500);

        if (ImGui::DragFloat("Boids radius", &radius, 0.01f, 0.01f, 0.2f))
        {
            boids.updateRadius(radius);
        }

        if (
            ImGui::DragFloat("Boids separation radius", &forcesConfig._separation_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Boids alignment radius", &forcesConfig._alignment_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Boids cohesion radius", &forcesConfig._cohesion_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Avoid Factor (Separation)", &forcesConfig._avoid_factor, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Matching Factor (Alignment)", &forcesConfig._matching_factor, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Centering Factor (Cohesion)", &forcesConfig._centering_factor, 0.01f, 0, 1.f)
        )
            boids.updateForcesConfig(forcesConfig);

        if (
            ImGui::DragFloat("Boids min speed", &behaviorConfig._minSpeed, 0.01f, 0.f, 5.f)
            || ImGui::DragFloat("Boids max speed", &behaviorConfig._maxSpeed, 0.01f, 0.f, 5.f)
        )
            boids.updateBehaviorConfig(behaviorConfig);

        if (ImGui::Button("Shape : Triangle"))
        {
            shape = Shapes::TwoDimensions::Triangle{radius};
            boids.updateShape(shape);
        }

        if (ImGui::Button("Shape : Circle"))
        {
            shape = Shapes::TwoDimensions::Circle{radius};
            boids.updateShape(shape);
        }

        if (ImGui::Button("Shape : Fish"))
        {
            shape = Shapes::TwoDimensions::Fish{radius};
            boids.updateShape(shape);
        }

        if (ImGui::Button("Reload flock"))
            load_boids();

        ImGui::End();
        // ImGui::ShowDemoWindow();
    };

    auto        obstacles      = Obstacles{};
    float const obstacleRadius = .1;
    obstacles.addRange({-ctx.aspect_ratio(), 1 + obstacleRadius}, {ctx.aspect_ratio(), 1 + obstacleRadius}, obstacleRadius);
    obstacles.addRange({-ctx.aspect_ratio(), -1 - obstacleRadius}, {ctx.aspect_ratio(), -1 - obstacleRadius}, obstacleRadius);
    obstacles.addRange({-ctx.aspect_ratio() - obstacleRadius, -1}, {-ctx.aspect_ratio() - obstacleRadius, 1}, obstacleRadius);
    obstacles.addRange({ctx.aspect_ratio() + obstacleRadius, -1}, {ctx.aspect_ratio() + obstacleRadius, 1}, obstacleRadius);

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        boids.updateAndDraw(ctx, obstacles);
        obstacles.draw(ctx);
    };

    ctx.start();
}