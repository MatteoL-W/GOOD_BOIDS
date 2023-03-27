#pragma once

#include <p6/p6.h>
#include "Boids/Configs.h"
#include "Food/FoodProvider.h"
#include "Obstacles/ObstaclesManager.h"
#include "Shapes/2D.h"
#include "utils/TransformAttributes.h"

// ToDo: Boid a deux reponsabilités. Faire un BoidMovement + Shape

class Boid {
public:
    explicit Boid(unsigned int _speciesId, Utils::TransformAttributes const&, ShapesType const&, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<Boid> const&, ObstaclesManager const&, FoodProvider&);
    void draw(p6::Context&);

    [[nodiscard]] unsigned int               getSpeciesId() const { return _speciesId; };
    [[nodiscard]] Utils::TransformAttributes getTransformAttributes() const { return _transformAttributes; };
    [[nodiscard]] glm::vec2                  getPosition() const { return _transformAttributes._position; };
    [[nodiscard]] glm::vec2                  getVelocity() const { return _transformAttributes._velocity; };
    [[nodiscard]] glm::vec2                  getAcceleration() const { return _transformAttributes._acceleration; };
    [[nodiscard]] float                      getRadius() const;

    void resetForces() { _transformAttributes._acceleration = glm::vec2{0}; };
    void setForcesConfig(ForcesConfig config) { _forcesConfig = config; };
    void setBehaviorConfig(BehaviorConfig config) { _behaviorConfig = config; };

    void addToPosition(glm::vec2 position) { _transformAttributes._position += position; };
    void addToVelocity(glm::vec2 velocity) { _transformAttributes._velocity += velocity; };
    void addToAcceleration(glm::vec2 velocity) { _transformAttributes._velocity += velocity; };

private:
    void addFoodAttraction(FoodProvider&);
    void addObstaclesAvoidance(ObstaclesManager const&);
    void addClassicBoidsForces(std::vector<Boid> const&);

    /// Return a vector containing all the boids nearby that share the same species
    [[nodiscard]] std::vector<Boid> getNearbyAndSameBoids(std::vector<Boid> const& boids, double radius) const;
    [[nodiscard]] std::vector<Boid> getNearbyBoids(std::vector<Boid> const& boids, double radius) const;

private:
    unsigned int               _speciesId;
    Utils::TransformAttributes _transformAttributes{};
    ShapesType                 _shape{};
    BehaviorConfig             _behaviorConfig{};
    ForcesConfig               _forcesConfig{};
};
