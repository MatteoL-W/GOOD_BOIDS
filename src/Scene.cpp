#include "Scene.h"
#include "Boids/Manager.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Lights/Directional.h"
#include "Rendering/Shapes/ShapesRegister.h"

void Scene::setupWorld(p6::Context& ctx)
{
    initializeBoids(ctx);

    _renderingDatas._directional = Rendering::Lights::Directional{{.0f, 3.0f, -2.f}, {1.f, 0.f, 0.f}, .1f, .4f, .5f};
    _renderingDatas._points      = {
        Rendering::Lights::Point{{-2.f, .1f, .0f}, 1.f, .09f, .032f, .1f, .4f, 1.f},
    };
    _renderingDatas._renderType = utils::RenderType::Classic;

    ctx.update = [&]() {
        updateMembers(ctx);
        renderDepthMap();
        render(ctx);
        //_debugDepthMap.render(ctx, _shadowMap.getDepthMapTextureId());
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
    _boidsManager.addSpecies(ctx, firstSpecies);

    ctx.imgui = [&]() {
        ImGui::Begin("My super GUI");

        GUI::showSpeciesGUI("Little boids", firstSpecies, _boidsManager);
        GUI::showFoodGUI(_foodProvider);

        ImGui::End();
    };
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
        _boidsManager.draw(
            utils::RenderingDatas{
                ._renderType       = utils::RenderType::DepthMap,
                ._lightSpaceMatrix = lightSpaceMatrix,
            }
        );
    });
}

void Scene::render(p6::Context& ctx)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, ctx.main_canvas_width(), ctx.main_canvas_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _renderingDatas._lightSpaceMatrix = _shadowMap.getLightSpaceMatrix();

    // ToDo: Refactor
    _shadowMap.bindTextureOnFirstUnit();
    _floor.draw({}, _renderingDatas);

    _shadowMap.bindTextureOnFirstUnit();
    _boidsManager.draw(_renderingDatas);

    _foodProvider.draw();
}