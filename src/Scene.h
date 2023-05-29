#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Engine/SkyBox.h"
#include "Rendering/Shadow/ShadowMap.h"
#include "Rendering/Shapes/List/Cube.h"
#include "Rendering/Shapes/List/Ground.h"
#include "Spectator/Spectator.h"
#include "utils/RenderingDatas.h"

class Scene {
public:
    void setupWorld(p6::Context&);

private:
    void initializeBoids(SceneRadius&);
    void loadSpecies(SceneRadius& sceneRadius);
    void initializeLights();
    void initializeSkyBox();
    void initializeImGui(std::function<void()>& imguiFn);

    void updateMembers(p6::Context&);
    void renderDepthMap();
    void render(glm::ivec2 canvasDimensions);

private:
    SceneRadius _sceneRadius{};

    Boids::Species _firstSpecies{Rendering::Shapes::getCloudInstance()};
    Boids::Species _secondSpecies{Rendering::Shapes::getPinkCloudInstance()};
    Boids::Species _thirdSpecies{Rendering::Shapes::getBlueCloudInstance()};
    Boids::Species _demoLODSpecies{Rendering::Shapes::getDebugLODInstance()};
    Boids::Manager _boidsManager{};

    Spectator::Spectator  _spectator{};
    Camera::CameraManager _cameraManager{Camera::getCameraInstance()};

    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{Features::ObstaclesConfig{}, true};

    utils::RenderingDatas        _renderingDatas{._renderType = utils::RenderType::Classic};
    Rendering::Shadow::ShadowMap _shadowMap{};

    Rendering::Engine::SkyBox _skyBox{};
    Rendering::Shapes::Cube   _cubeMap{_sceneRadius.value};
    Rendering::Shapes::Ground _floor{_sceneRadius.value};
};
