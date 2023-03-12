#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids/Boids.h"
#include "Food/FoodProvider.h"
#include "Helper/ImGuiHelper.hpp"
#include "Obstacles/Obstacles.h"
#include "Shapes/2D.h"
#include "Species/Species.h"

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

    auto behaviorConfig = BehaviorConfig{};
    auto forcesConfig   = ForcesConfig{
          ._separationRadius = 0.1f,
          ._alignmentRadius  = 0.23f,
          ._cohesionRadius   = 0.1f,
    };
    auto foodConfig   = FoodConfig{};
    auto foodProvider = FoodProvider{foodConfig};
    foodProvider.enableRandomFood();

    Boids boids{};
    int   numberOfBoids = 25;
    float radius        = .02f;

    auto prey     = Species{Shapes::TwoDimensions::Triangle{radius}, SpeciesType::Prey};
    auto predator = Species{Shapes::TwoDimensions::Fish{radius}, SpeciesType::Predator};

    auto load_boids = [&]() {
        boids.reset();
        boids.addSpecies(ctx, static_cast<unsigned int>(numberOfBoids), prey, behaviorConfig, forcesConfig);
        boids.addSpecies(ctx, static_cast<unsigned int>(numberOfBoids), predator, behaviorConfig, forcesConfig);
    };
    load_boids();

    ctx.imgui = [&]() {
        ImGui::Begin("Boids");

        BoidsHelper::load_boids_helper(boids, numberOfBoids, radius);
        BoidsHelper::load_forces_helper(boids, forcesConfig);
        BoidsHelper::load_behaviour_helper(boids, behaviorConfig);
        // BoidsHelper::load_shapes_helper(boids, shape, radius);
        BoidsHelper::load_food_helper(foodProvider, foodConfig);

        if (ImGui::Button("Reload flock"))
            load_boids();

        if (ImGui::Button("Reset settings"))
        {
            behaviorConfig = BehaviorConfig{};
            forcesConfig   = ForcesConfig{};
            foodConfig     = FoodConfig{};
        }

        // ImGui::ShowDemoWindow();
        ImGui::End();
    };

    auto        obstacles      = Obstacles{};
    float const obstacleRadius = .1f;
    obstacles.addRange({-ctx.aspect_ratio(), 1 + obstacleRadius}, {ctx.aspect_ratio(), 1 + obstacleRadius}, obstacleRadius);
    obstacles.addRange({-ctx.aspect_ratio(), -1 - obstacleRadius}, {ctx.aspect_ratio(), -1 - obstacleRadius}, obstacleRadius);
    obstacles.addRange({-ctx.aspect_ratio() - obstacleRadius, -1}, {-ctx.aspect_ratio() - obstacleRadius, 1}, obstacleRadius);
    obstacles.addRange({ctx.aspect_ratio() + obstacleRadius, -1}, {ctx.aspect_ratio() + obstacleRadius, 1}, obstacleRadius);
    obstacles.addOne({0, 0}, 0.1);

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);

        foodProvider.update(ctx);
        foodProvider.draw(ctx);

        boids.updateAndDraw(ctx, obstacles, foodProvider);

        obstacles.draw(ctx);
    };

    ctx.start();
}