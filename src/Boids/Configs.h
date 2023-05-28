#pragma once

namespace Boids {

struct BehaviorConfig {
    float _minSpeed             = .005f;
    float _maxSpeed             = .01f;
    float _foodAttractionRadius = 0.6f;
};

struct ForcesConfig {
    float _turnFactor = .8f;

    float _separationRadius = .7f;
    float _separationFactor = .1f;
    float _alignmentRadius  = 1.5f;
    float _alignmentFactor  = 1.5f;
    float _cohesionRadius   = 1.f;
    float _cohesionFactor   = 0.1f;
};

} // namespace Boids