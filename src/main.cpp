#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids/Boids.h"
#include "Food/FoodProvider.h"
#include "Helper/ImGuiHelper.hpp"
#include "Obstacles/Obstacles.h"
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

    // Lil Fish
    float lilFishRadius   = .01f;
    int   lilFishQuantity = 30;
    auto  lilFishShape    = Shapes::TwoDimensions::Fish{lilFishRadius};
    auto  lilFishForces   = ForcesConfig{._separationRadius = 0.05f, ._separationFactor = 0.01f, ._alignmentRadius = .2f, ._alignmentFactor = .5f, ._cohesionRadius = .2f, ._cohesionFactor = .5f};
    auto  lilFishBehavior = BehaviorConfig{._minSpeed = .008f, ._maxSpeed = 0.011f, ._foodAttractionRadius = 0.6f};
    auto  lilFishInit     = Species{._shape = lilFishShape, ._quantity = lilFishQuantity, ._behaviorConfig = lilFishBehavior, ._forcesConfig = lilFishForces};

    // Mid Fish
    float midFishRadius   = .03f;
    int   midFishQuantity = 7;
    auto  midFishShape    = Shapes::TwoDimensions::Fish{midFishRadius};
    auto  midFishForces   = ForcesConfig{._separationRadius = 0.06f, ._alignmentRadius = 0.23f, ._cohesionRadius = 0.1f};
    auto  midFishBehavior = BehaviorConfig{._minSpeed = .005f, ._maxSpeed = .008f, ._foodAttractionRadius = 0.8f};
    auto  midFishInit     = Species{._shape = midFishShape, ._quantity = midFishQuantity, ._behaviorConfig = midFishBehavior, ._forcesConfig = midFishForces};

    // Big Fish
    float bigFishRadius   = .07f;
    int   bigFishQuantity = 3;
    auto  bigFishShape    = Shapes::TwoDimensions::Fish{bigFishRadius};
    auto  bigFishForces   = ForcesConfig{._separationRadius = 0.13f, ._alignmentRadius = 0.25f, ._cohesionRadius = 0.3f};
    auto  bigFishBehavior = BehaviorConfig{._minSpeed = .003f, ._maxSpeed = .004f, ._foodAttractionRadius = 0.4f};
    auto  bigFishInit     = Species{._shape = bigFishShape, ._quantity = bigFishQuantity, ._behaviorConfig = bigFishBehavior, ._forcesConfig = bigFishForces};

    auto foodConfig   = FoodConfig{};
    auto foodProvider = FoodProvider{foodConfig};
    foodProvider.enableRandomFood();

    Boids boids{};
    auto  load_boids = [&]() {
        boids.reset();
        boids.addSpecies(ctx, lilFishInit);
        boids.addSpecies(ctx, midFishInit);
        boids.addSpecies(ctx, bigFishInit);
    };
    load_boids();

    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        if (ImGui::CollapsingHeader("Lil boids"))
        {
            // BoidsHelper::load_boids_helper(boids, lilFishQuantity, lilFishRadius);
            BoidsHelper::load_forces_helper(boids, lilFishForces);
            BoidsHelper::load_behaviour_helper(boids, lilFishBehavior);
            // BoidsHelper::load_shapes_helper(boids, shape, radius);
        }

        if (ImGui::CollapsingHeader("Mid boids"))
        {
            BoidsHelper::load_forces_helper(boids, midFishForces);
            BoidsHelper::load_behaviour_helper(boids, midFishBehavior);
        }

        if (ImGui::CollapsingHeader("Big boids"))
        {
            BoidsHelper::load_forces_helper(boids, bigFishForces);
            BoidsHelper::load_behaviour_helper(boids, bigFishBehavior);
        }

        BoidsHelper::load_food_helper(foodProvider, foodConfig);

        if (ImGui::Button("Reload flock"))
            load_boids();

        // ToDo
        // if (ImGui::Button("Reset settings"))

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