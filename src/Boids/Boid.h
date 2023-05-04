#pragma once

#include <p6/p6.h>
#include "Boids/Configs.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "Movement.h"
#include "Rendering/Shapes/ShapesRegister.h"
#include "utils/RenderingDatas.h"
#include "utils/TransformAttributes.h"

namespace Boids {

class Boid {
public:
    explicit Boid(unsigned int _speciesId, ShapesType const&, utils::TransformAttributes const&, BehaviorConfig const&, ForcesConfig const&);

    void update(std::vector<Boid> const&, Features::ObstaclesManager const&, Features::FoodProvider&);
    void draw(utils::RenderingDatas&);

    void         setForcesConfig(ForcesConfig config) { _movement.setForcesConfig(config); };
    void         setBehaviorConfig(BehaviorConfig config) { _movement.setBehaviorConfig(config); };
    Movement     getMovement() const { return _movement; };
    unsigned int getSpeciesId() const { return _speciesId; };

private:
    [[nodiscard]] float getRadius() const;

private:
    unsigned int      _speciesId{};
    ShapesType const& _shape;
    Movement          _movement{};
};

} // namespace Boids