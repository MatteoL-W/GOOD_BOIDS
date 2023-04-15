#include <p6/p6.h>
#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <cstdlib>
#include "Boids/BoidsManager.h"
#include "Cameras/CameraManager.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Rendering/Shapes/3D.h"
#include "tiny_gltf.h"

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

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto firstSpecies = Species{
        Shapes::ThreeDimensions::getDuckInstance(),
        10,
        {._minSpeed = .020f, ._maxSpeed = 0.025f, ._foodAttractionRadius = 0.6f},
        {._separationRadius = 0.13f, ._separationFactor = 0.01f, ._alignmentRadius = .3f, ._alignmentFactor = .5f, ._cohesionRadius = .3f, ._cohesionFactor = .5f},
    };

    auto secondSpecies = Species{
        Shapes::ThreeDimensions::getConeInstance(0.2f),
        5,
        {._minSpeed = .015f, ._maxSpeed = 0.020f, ._foodAttractionRadius = 0.8f},
        {._separationRadius = 0.35f, ._separationFactor = 0.01f, ._alignmentRadius = .5f, ._alignmentFactor = .5f, ._cohesionRadius = .5f, ._cohesionFactor = .5f},
    };

    auto       boidsManager = BoidsManager{};
    auto const load_boids   = [&]() {
        boidsManager.reset();
        boidsManager.addSpecies(ctx, firstSpecies);
        boidsManager.addSpecies(ctx, secondSpecies);
    };
    load_boids();

    auto foodProvider = Features::FoodProvider{Features::FoodConfig{}, true};

    auto obstaclesManager = Features::ObstaclesManager{};
    // obstaclesManager.add2DMapDelimiters(ctx.aspect_ratio(), 1);
    // obstaclesManager.addRange({-2.f, 0.f, 0.f}, {2.f, 2.f, 0.f}, 0.1f);
    // obstaclesManager.add3DMapDelimiters();

    auto cameraManager = Camera::getCameraInstance();

    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        GUI::showSpeciesGUI("Little boids", firstSpecies, boidsManager);
        GUI::showSpeciesGUI("Middle boids", secondSpecies, boidsManager);

        GUI::showFoodGUI(foodProvider);

        if (ImGui::Button("Reload flock"))
            load_boids();

        // ToDo : Reset settings
        // ImGui::ShowDemoWindow();
        ImGui::End();
    };

    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Gray);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cameraManager.handleEvents(ctx);

        foodProvider.update(ctx);
        foodProvider.draw(ctx);

        boidsManager.update(obstaclesManager, foodProvider);
        boidsManager.draw(ctx);

        //obstaclesManager.draw(ctx);
    };

    ctx.start();
}