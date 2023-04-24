#pragma once

#include <p6/p6.h>
#include "Boids/Manager.h"
#include "Rendering/Lights/Directional.h"

class Scene {
public:
    void setupWorld(p6::Context&);

private:
    void initializeBoids(p6::Context&);
    void initializeImGuiBoids(p6::Context& ctx, auto addSpeciesFn, auto loadBoidsFn);

    void updateMembers(p6::Context&);
    void renderToDepthMap(p6::Context&);
    void render(p6::Context&);

private:
    Boids::Manager             boidsManager{};
    Features::FoodProvider     foodProvider{Features::FoodConfig{}, true};
    Features::ObstaclesManager obstaclesManager{};

    Light::Directional       directional{glm::vec3{1.f, 1.f, 1.f}};
    Rendering::Shapes::Plane floor{0.1f};
};
