#pragma once

#include <p6/p6.h>
#include "Boids/Configs.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "Movement.h"
#include "Rendering/Shapes/ShapesRegister.h"
#include "Species.h"
#include "utils/RenderingDatas.h"
#include "utils/StrongType.h"
#include "utils/TransformAttributes.h"

namespace Boids {

class Boid {
public:
    explicit Boid(Species&, utils::TransformAttributes const&);

    void update(std::vector<Boid> const&, Features::ObstaclesManager const&, Features::FoodProvider&, SceneRadius& sceneRadius);
    void draw(utils::RenderingDatas&);

    void         setForcesConfig(ForcesConfig config) { _movement.setForcesConfig(config); };
    void         setBehaviorConfig(BehaviorConfig config) { _movement.setBehaviorConfig(config); };
    Movement     getMovement() const { return _movement; };
    unsigned int getSpeciesId() const { return _species._id; };

private:
    [[nodiscard]] float getRadius() const;

private:
    Species& _species;
    Movement _movement;
};

} // namespace Boids