#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids/Boids.h"
#include "Food/FoodProvider.h"
#include "GUI/ImGui.hpp"
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

    auto firstSpecies = Species{
        ._shape          = Shapes::TwoDimensions::Fish{.01f},
        ._quantity       = 30,
        ._behaviorConfig = {._minSpeed = .008f, ._maxSpeed = 0.011f, ._foodAttractionRadius = 0.6f},
        ._forcesConfig   = {._separationRadius = 0.05f, ._separationFactor = 0.01f, ._alignmentRadius = .2f, ._alignmentFactor = .5f, ._cohesionRadius = .2f, ._cohesionFactor = .5f},
    };

    auto secondSpecies = Species{
        ._shape          = Shapes::TwoDimensions::Fish{.03f},
        ._quantity       = 7,
        ._behaviorConfig = {._minSpeed = .005f, ._maxSpeed = .008f, ._foodAttractionRadius = 0.8f},
        ._forcesConfig   = {._separationRadius = 0.06f, ._alignmentRadius = 0.23f, ._cohesionRadius = 0.1f},
    };

    auto bigFishInit = Species{
        ._shape          = Shapes::TwoDimensions::Fish{.07f},
        ._quantity       = 3,
        ._behaviorConfig = {._minSpeed = .003f, ._maxSpeed = .004f, ._foodAttractionRadius = 0.4f},
        ._forcesConfig   = {._separationRadius = 0.13f, ._alignmentRadius = 0.25f, ._cohesionRadius = 0.3f},
    };

    auto foodProvider = FoodProvider{FoodConfig{}, true};

    Boids boids{};
    auto  load_boids = [&]() {
        boids.reset();
        boids.addSpecies(ctx, firstSpecies);
        boids.addSpecies(ctx, secondSpecies);
        boids.addSpecies(ctx, bigFishInit);
    };
    load_boids();

    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        GUI::showSpeciesGUI("Little boids", firstSpecies, boids);
        GUI::showSpeciesGUI("Middle boids", secondSpecies, boids);
        GUI::showSpeciesGUI("Big boids", bigFishInit, boids);
        GUI::showFoodGUI(foodProvider);

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