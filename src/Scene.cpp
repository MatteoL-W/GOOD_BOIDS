#include "Scene.h"
#include "Boids/Manager.h"
#include "Features/ObstaclesManager.h"
#include "GUI/GUI.hpp"
#include "Rendering/Cameras/CameraManager.h"
#include "Rendering/Lights/Directional.h"
#include "Rendering/Shapes/List/Plane.h"
#include "Rendering/Shapes/ShapesRegister.h"
#include "utils/TransformAttributes.h"

void Scene::setupWorld(p6::Context& ctx)
{
    initializeBoids(ctx);
    initializeLights();

    ctx.update = [&]() {
        updateMembers(ctx);
        renderDepthMap();
        render(ctx);
        //        _debugDepthMap.render(ctx, _shadowMap.getDepthMapTextureId());
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

void Scene::initializeLights()
{
    _renderingDatas._directional = Rendering::Lights::Directional{{.0f, 3.0f, -2.f}, {0.f, -1.f, 0.f}, .1f, .2f, .3f};
    _renderingDatas._points      = {
        Rendering::Lights::Point{Spectator::getSpectatorPosition(), 1.f, .09f, .032f, .05f, .4f, 1.f},
    };
}

void Scene::updateMembers(p6::Context& ctx)
{
    auto cameraManager = Camera::getCameraInstance();
    cameraManager.handleEvents(ctx);

    _renderingDatas._lightSpaceMatrix = _shadowMap.getLightSpaceMatrix();

    _foodProvider.update(ctx);
    _boidsManager.update(_obstaclesManager, _foodProvider, _sceneRadius);

    _renderingDatas._points[0].setPosition(Spectator::getSpectatorPosition());
}

void Scene::renderDepthMap()
{
    if (!_renderingDatas._directional.has_value())
        return;

    _shadowMap.renderDepthMap(
        [&](glm::mat4 lightSpaceMatrix) {
            _boidsManager.draw(
                utils::RenderingDatas{
                    ._renderType       = utils::RenderType::DepthMap,
                    ._lightSpaceMatrix = lightSpaceMatrix,
                }
            );
        },
        _renderingDatas._directional.value()
    );
}

void Scene::render(p6::Context& ctx)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glViewport(0, 0, ctx.main_canvas_width(), ctx.main_canvas_height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _shadowMap.bindTextureOnFirstUnit();

    _floor.draw({._position = glm::vec3{0.f, -_sceneRadius + .1f, 0.f}}, _renderingDatas);
    _boidsManager.draw(_renderingDatas);
    _spectator.draw();
    _foodProvider.draw();

    _skyBox.draw();
    _cubeMap.draw();
}
