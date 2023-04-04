#pragma once

#include <p6/p6.h>
#include "Boids/Configs.h"
#include "Boids/IForEachBoidMovement.h"
#include "Features/FoodProvider.h"
#include "Features/ObstaclesManager.h"
#include "utils/TransformAttributes.h"

class BoidMovement {
public:
    BoidMovement() = default;
    explicit BoidMovement(unsigned int _speciesId, Utils::TransformAttributes const&, BehaviorConfig const&, ForcesConfig const&);
    void update(IForEachBoidMovement const&, Features::ObstaclesManager const&, Features::FoodProvider&, float boidRadius);

    [[nodiscard]] unsigned int               getSpeciesId() const { return _speciesId; };
    [[nodiscard]] Utils::TransformAttributes getTransformAttributes() const { return _transformAttributes; };
    [[nodiscard]] glm::vec3                  getPosition() const { return _transformAttributes._position; };
    [[nodiscard]] glm::vec3                  getVelocity() const { return _transformAttributes._velocity; };
    [[nodiscard]] glm::vec3                  getAcceleration() const { return _transformAttributes._acceleration; };

    void resetForces() { _transformAttributes._acceleration = glm::vec3{0}; };
    void setForcesConfig(ForcesConfig& config) { _forcesConfig = config; };
    void setBehaviorConfig(BehaviorConfig& config) { _behaviorConfig = config; };

    void addToPosition(glm::vec3 position) { _transformAttributes._position += position; };
    void addToVelocity(glm::vec3 velocity) { _transformAttributes._velocity += velocity; };
    void addToAcceleration(glm::vec3 velocity) { _transformAttributes._velocity += velocity; };

private:
    void addFoodAttraction(Features::FoodProvider&);
    void addObstaclesAvoidance(Features::ObstaclesManager const&, float boidRadius);
    void addClassicBoidsForces(IForEachBoidMovement const&, float boidRadius);

    /// Return a vector containing all the boids nearby that share the same species
    [[nodiscard]] std::vector<BoidMovement> getNearbyAndSameBoids(IForEachBoidMovement const& boids, float boidRadius, float proximityRadius) const;
    [[nodiscard]] std::vector<BoidMovement> getNearbyBoids(IForEachBoidMovement const& boids, float boidRadius, float proximityRadius) const;

private:
    unsigned int               _speciesId{};
    Utils::TransformAttributes _transformAttributes{};
    BehaviorConfig             _behaviorConfig{};
    ForcesConfig               _forcesConfig{};
};
