#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Engine/SkyBox.h"
#include "Rendering/Shadow/DebugDepthMap.h"
#include "Rendering/Shadow/ShadowMap.h"
#include "Rendering/Shapes/List/Cube.h"
#include "Rendering/Shapes/List/Plane.h"
#include "Rendering/Shapes/ShapesRegister.h"
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
    float          _sceneRadius = 5.f;
    Boids::Manager _boidsManager{};

    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{};

    utils::RenderingDatas            _renderingDatas{._renderType = utils::RenderType::Classic};
    Rendering::Shadow::ShadowMap     _shadowMap{};
    Rendering::Shadow::DebugDepthMap _debugDepthMap{};

    Rendering::Engine::SkyBox _skyBox{};
    Rendering::Shapes::Cube   _cubeMap{_sceneRadius};
    Rendering::Shapes::Plane  _floor{_sceneRadius};
};
