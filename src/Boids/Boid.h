#pragma once

#include <p6/p6.h>
#include "BoidMovement.h"
#include "Boids/Configs.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "Shapes/3D.h"
#include "utils/TransformAttributes.h"

class Boid {
public:
    explicit Boid(unsigned int _speciesId, ShapesType const&, Utils::TransformAttributes const&, BehaviorConfig const&, ForcesConfig const&);

    void update(std::vector<Boid> const&, Features::ObstaclesManager const&, Features::FoodProvider&);
    void draw(p6::Context&);

    void         setForcesConfig(ForcesConfig config) { _movement.setForcesConfig(config); };
    void         setBehaviorConfig(BehaviorConfig config) { _movement.setBehaviorConfig(config); };
    BoidMovement getMovement() const { return _movement; };
    unsigned int getSpeciesId() const { return _speciesId; };

private:
    [[nodiscard]] float getRadius() const;

private:
    unsigned int      _speciesId{};
    ShapesType const& _shape;
    BoidMovement      _movement{};
};
