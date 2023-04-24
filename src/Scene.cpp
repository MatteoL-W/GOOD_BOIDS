#include "Scene.h"
#include "Boids/Manager.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Shapes/ShapesRegister.h"

void Scene::setupWorld(p6::Context& ctx)
{
    initializeBoids(ctx);

    ctx.update = [&]() {
        updateMembers(ctx);
        renderToDepthMap(ctx);
        render(ctx);
    };
}

void Scene::updateMembers(p6::Context& ctx)
{
    auto cameraManager = Camera::getCameraInstance();
    cameraManager.handleEvents(ctx);

    foodProvider.update(ctx);
    boidsManager.update(obstaclesManager, foodProvider);
}

void Scene::renderToDepthMap(p6::Context& ctx)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    auto renderCastersShadows = [&](glm::mat4 lightSpaceMatrix) {
        boidsManager.draw(ctx, true, lightSpaceMatrix);
    };
    directional.renderDepthMap(renderCastersShadows);
}

void Scene::render(p6::Context& ctx)
{
    glViewport(0, 0, ctx.main_canvas_width(), ctx.main_canvas_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ctx.background(p6::NamedColor::Gray);

    foodProvider.draw(ctx);
    boidsManager.draw(ctx);
    floor.draw(ctx, {});
}

void Scene::initializeBoids(p6::Context& ctx)
{
    auto firstSpecies = Boids::Species{
        Rendering::Shapes::getDuckInstance(),
        10,
        {._minSpeed = .020f, ._maxSpeed = 0.025f, ._foodAttractionRadius = 0.6f},
        {._separationRadius = 0.13f, ._separationFactor = 0.01f, ._alignmentRadius = .3f, ._alignmentFactor = .5f, ._cohesionRadius = .3f, ._cohesionFactor = .5f},
    };

    auto secondSpecies = Boids::Species{
        Rendering::Shapes::getConeInstance(0.2f),
        5,
        {._minSpeed = .015f, ._maxSpeed = 0.020f, ._foodAttractionRadius = 0.8f},
        {._separationRadius = 0.35f, ._separationFactor = 0.01f, ._alignmentRadius = .5f, ._alignmentFactor = .5f, ._cohesionRadius = .5f, ._cohesionFactor = .5f},
    };

    auto addSpeciesToGUI = [&]() {
        GUI::showSpeciesGUI("Little boids", firstSpecies, boidsManager);
        GUI::showSpeciesGUI("Middle boids", secondSpecies, boidsManager);
    };

    auto const load_boids = [&]() {
        boidsManager.reset();
        boidsManager.addSpecies(ctx, firstSpecies);
        boidsManager.addSpecies(ctx, secondSpecies);
    };
    load_boids();

    initializeImGuiBoids(ctx, addSpeciesToGUI, load_boids);
}

void Scene::initializeImGuiBoids(p6::Context& ctx, auto addSpeciesFn, auto loadBoidsFn)
{
    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        addSpeciesFn();
        GUI::showFoodGUI(foodProvider);

        if (ImGui::Button("Reload flock"))
            loadBoidsFn();

        // ToDo : Reset settings
        // ImGui::ShowDemoWindow();
        ImGui::End();
    };
}