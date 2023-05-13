#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Engine/SkyBox.h"
#include "Rendering/Shadow/DebugDepthMap.h"
#include "Rendering/Shadow/ShadowMap.h"
#include "Rendering/Shapes/List/Cube.h"
#include "Rendering/Shapes/List/Plane.h"
#include "Spectator/Spectator.h"
#include "utils/RenderingDatas.h"

class Scene {
public:
    void setupWorld(p6::Context&);

private:
    void initializeBoids(p6::Context&);
    void initializeLights();

    void updateMembers(p6::Context&);
    void renderDepthMap();
    void render(p6::Context&);

private:
    float _sceneRadius = 5.f;

    Boids::Species firstSpecies{
        ._shape          = Rendering::Shapes::getDuckInstance(),
        ._quantity       = 1,
        ._behaviorConfig = {._minSpeed = .020f, ._maxSpeed = 0.025f, ._foodAttractionRadius = 0.6f},
        ._forcesConfig   = {._separationRadius = 0.13f, ._separationFactor = 0.01f, ._alignmentRadius = .3f, ._alignmentFactor = .5f, ._cohesionRadius = .3f, ._cohesionFactor = .5f},
    };
    Boids::Species secondSpecies{
        ._shape          = Rendering::Shapes::getDuckInstance(),
        ._quantity       = 1,
        ._behaviorConfig = {._minSpeed = .050f, ._maxSpeed = 0.075f, ._foodAttractionRadius = 0.6f},
        ._forcesConfig   = {._separationRadius = 0.13f, ._separationFactor = 0.01f, ._alignmentRadius = .3f, ._alignmentFactor = .5f, ._cohesionRadius = .3f, ._cohesionFactor = .5f},
    };
    Boids::Manager _boidsManager{};

    Spectator::Spectator  _spectator{};
    Camera::CameraManager _cameraManager{Camera::getCameraInstance()};

    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{};

    utils::RenderingDatas            _renderingDatas{._renderType = utils::RenderType::Classic};
    Rendering::Shadow::ShadowMap     _shadowMap{};
    Rendering::Shadow::DebugDepthMap _debugDepthMap{};

    Rendering::Engine::SkyBox _skyBox{};
    Rendering::Shapes::Cube   _cubeMap{_sceneRadius};
    Rendering::Shapes::Plane  _floor{_sceneRadius};
};
