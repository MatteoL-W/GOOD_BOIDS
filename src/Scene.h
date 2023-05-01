#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Shadow/DebugDepthMap.h"
#include "Rendering/Shadow/ShadowMap.h"
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
    Boids::Manager _boidsManager{};

    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{};

    utils::RenderingDatas            _renderingDatas{._renderType = utils::RenderType::Classic};
    Rendering::Shadow::ShadowMap     _shadowMap{};
    Rendering::Shadow::DebugDepthMap _debugDepthMap{};

    // ToDo: Won't be here later
    Rendering::Shapes::Plane _floor{0.1f};
};
