#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids/BoidsManager.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Shapes/3D.h"

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
        Shapes::ThreeDimensions::Sphere{.1f},
        10,
        {._minSpeed = .008f, ._maxSpeed = 0.011f, ._foodAttractionRadius = 0.6f},
        {._separationRadius = 0.05f, ._separationFactor = 0.01f, ._alignmentRadius = .2f, ._alignmentFactor = .5f, ._cohesionRadius = .2f, ._cohesionFactor = .5f},
    };

    auto secondSpecies = Species{
        Shapes::ThreeDimensions::Sphere{.03f},
        7,
        {._minSpeed = .005f, ._maxSpeed = .008f, ._foodAttractionRadius = 0.8f},
        {._separationRadius = 0.06f, ._alignmentRadius = 0.23f, ._cohesionRadius = 0.1f},
    };

    auto thirdSpecies = Species{
        Shapes::ThreeDimensions::Sphere{.07f},
        3,
        {._minSpeed = .003f, ._maxSpeed = .004f, ._foodAttractionRadius = 0.4f},
        {._separationRadius = 0.13f, ._alignmentRadius = 0.25f, ._cohesionRadius = 0.3f},
    };

    auto       boidsManager = BoidsManager{};
    auto const load_boids   = [&]() {
        boidsManager.reset();
        boidsManager.addSpecies(ctx, firstSpecies);
        //boidsManager.addSpecies(ctx, secondSpecies);
        //boidsManager.addSpecies(ctx, thirdSpecies);
    };
    load_boids();

    auto foodProvider = Features::FoodProvider{Features::FoodConfig{}, true};

    auto obstaclesManager = Features::ObstaclesManager{};
    // obstaclesManager.add2DMapDelimiters(ctx.aspect_ratio(), 1);
    // obstaclesManager.addOne({0, 0}, 0.1f);

    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        GUI::showSpeciesGUI("Little boids", firstSpecies, boidsManager);
        GUI::showSpeciesGUI("Middle boids", secondSpecies, boidsManager);
        GUI::showSpeciesGUI("Big boids", thirdSpecies, boidsManager);
        GUI::showFoodGUI(foodProvider);

        if (ImGui::Button("Reload flock"))
            load_boids();

        // ToDo : Reset settings
        // ImGui::ShowDemoWindow();
        ImGui::End();
    };

    auto testShader = p6::load_shader("../src/Shaders/3D.vs.glsl", "../src/Shaders/normal.fs.glsl");

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);

        foodProvider.update(ctx);
        //foodProvider.draw(ctx, testShader);

        boidsManager.update(obstaclesManager, foodProvider);
        boidsManager.draw(ctx, testShader);

        //obstaclesManager.draw(ctx, testShader);
    };

    ctx.start();
}