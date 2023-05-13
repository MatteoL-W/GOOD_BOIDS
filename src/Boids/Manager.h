#pragma once

#include <p6/p6.h>
#include <utility>
#include <variant>
#include "Boid.h"
#include "Boids/Configs.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "Rendering/Shapes/ShapesRegister.h"
#include "Species.h"
#include "utils/RenderingDatas.h"

namespace Boids {

class Manager {
public:
    Manager() = default;
    void addSpecies(SceneRadius&, Species&);

    void update(Features::ObstaclesManager const&, Features::FoodProvider&, SceneRadius& sceneRadius);
    void draw(utils::RenderingDatas& renderingDatas);

    void reset() { _boids.clear(); };

private:
    std::vector<Boid> _boids{};
};

} // namespace Boids
