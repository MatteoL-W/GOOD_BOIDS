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
        renderDepthMap();
        render(ctx);
        _debugDepthMap.render(ctx, _shadowMap.getDepthMapTextureId());
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

    auto const load_boids = [&]() {
        _boidsManager.reset();
        _boidsManager.addSpecies(ctx, firstSpecies);
    };
    load_boids();

    auto addSpeciesToGUI = [&]() {
        GUI::showSpeciesGUI("Little boids", firstSpecies, _boidsManager);
    };

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
    _shadowMap.renderDepthMap([&](glm::mat4 lightSpaceMatrix) {
        _boidsManager.draw(true, lightSpaceMatrix);
        _floor.drawDepthMap({}, lightSpaceMatrix);
    });
}

void Scene::render(p6::Context& ctx)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, ctx.main_canvas_width(), ctx.main_canvas_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shadowMap.bindTextureOnFirstUnit();
    _floor.draw({}, _shadowMap.getLightSpaceMatrix());

    _shadowMap.bindTextureOnFirstUnit();
    _boidsManager.draw(false, _shadowMap.getLightSpaceMatrix());

    _foodProvider.draw();
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
