#include "Scene.h"
#include "Boids/Manager.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Shapes/ShapesRegister.h"

void Scene::setupWorld(p6::Context& ctx)
{
    initializeBoids(ctx);

    // ToDo: I think this shouldn't be here
    auto& projectionMatrixHandler = utils::getProjectionMatrixHandlerInstance();
    projectionMatrixHandler.setProjection(ctx.aspect_ratio());

    ctx.main_canvas_resized = [&]() {
        projectionMatrixHandler.setProjection(ctx.aspect_ratio());
    };
    // End

    ctx.update = [&]() {
        updateMembers(ctx);
        renderDepthMap();
        render(ctx);
    };
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
        GUI::showSpeciesGUI("Little boids", firstSpecies, _boidsManager);
        //GUI::showSpeciesGUI("Middle boids", secondSpecies, _boidsManager);
    };

    auto const load_boids = [&]() {
        _boidsManager.reset();
        _boidsManager.addSpecies(ctx, firstSpecies);
        _boidsManager.addSpecies(ctx, secondSpecies);
    };
    load_boids();

    initializeImGui(ctx, addSpeciesToGUI, load_boids);
}

void Scene::updateMembers(p6::Context& ctx)
{
    auto cameraManager = Camera::getCameraInstance();
    cameraManager.handleEvents(ctx);

    _foodProvider.update(ctx);
    _boidsManager.update(_obstaclesManager, _foodProvider);
}

void Scene::renderDepthMap()
{
    _directional.renderDepthMap([&](glm::mat4 lightSpaceMatrix) {
        _boidsManager.draw(true, lightSpaceMatrix);
    });
}

void Scene::render(p6::Context& ctx)
{
    glClearColor(1.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, ctx.main_canvas_width(), ctx.main_canvas_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _foodProvider.draw();
    _boidsManager.draw(false, _directional.getLightSpaceMatrix());
    _floor.draw({});
}

// ToDo: Move this function away
void Scene::initializeImGui(p6::Context& ctx, auto addSpeciesFn, auto loadBoidsFn)
{
    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        addSpeciesFn();
        GUI::showFoodGUI(_foodProvider);

        if (ImGui::Button("Reload boids"))
            loadBoidsFn();

        // ToDo : Reset settings
        // ImGui::ShowDemoWindow();
        ImGui::End();
    };
}