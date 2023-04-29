#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Shadow/DebugDepthMap.h"
#include "Rendering/Shadow/ShadowMap.h"
#include "utils/RenderType.h"

class Scene {
public:
    void setupWorld(p6::Context&);

private:
    void initializeBoids(p6::Context&);
    void initializeImGui(p6::Context&, auto addSpeciesFn, auto loadBoidsFn);

    void updateMembers(p6::Context&);
    void renderDepthMap();
    void render(p6::Context&);

private:
    Boids::Manager _boidsManager{};

    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{};

    Rendering::Lighting::ShadowMap     _shadowMap{};
    Rendering::Lighting::DebugDepthMap _debugDepthMap{};

    // ToDo: Won't be here later
    Rendering::Shapes::Plane _floor{0.1f};
};
