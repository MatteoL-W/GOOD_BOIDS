#pragma once

namespace Boids {

struct BehaviorConfig {
    float _minSpeed             = .005f;
    float _maxSpeed             = .01f;
    float _foodAttractionRadius = 0.6f;
};

struct ForcesConfig {
    float _separationRadius = .1f;
    float _separationFactor = .1f;
    float _alignmentRadius  = .2f;
    float _alignmentFactor  = .4f;
    float _cohesionRadius   = .2f;
    float _cohesionFactor   = .4f;

    float _turnFactor = .4f;
};

} // namespace Boids