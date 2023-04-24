#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Lighting/ShadowMap.h"
#include "utils/ProjectionMatrixHandler.h"

class Scene {
public:
    void setupWorld(p6::Context&);

private:
    void initializeBoids(p6::Context&);
    void initializeImGui(p6::Context&, auto addSpeciesFn, auto loadBoidsFn);

    void updateMembers(p6::Context&);
    void render(p6::Context&);

private:
    Boids::Manager             _boidsManager{};
    Features::FoodProvider     _foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager _obstaclesManager{};

    Lighting::ShadowMap       _directional{glm::vec3{1.f, 1.f, 1.f}};
    Rendering::Shapes::Plane _floor{0.1f};
};
