#pragma once

#include <p6/p6.h>
#include "Food/FoodProvider.h"
#include "Obstacles/Obstacles.h"
#include "Species/Species.h"
#include "utils/TransformAttributes.h"

struct BehaviorConfig {
    float _minSpeed               = .005f;
    float _maxSpeed               = .2f;
    float _food_attraction_radius = 0.3f;
};

struct ForcesConfig {
    float _separation_radius = .1f;
    float _avoid_factor      = .1f;
    float _alignment_radius  = .2f;
    float _matching_factor   = .1f;
    float _cohesion_radius   = .1f;
    float _centering_factor  = .1f;
};

class SingleBoid {
public:
    explicit SingleBoid(utils::TransformAttributes const&, Species const&, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<SingleBoid> const&, Obstacles const&, FoodProvider&);
    void draw(p6::Context&);

    [[nodiscard]] utils::TransformAttributes getTransformAttributes() const { return _transformAttributes; };
    [[nodiscard]] glm::vec2                  getPosition() const { return _transformAttributes._position; };
    [[nodiscard]] glm::vec2                  getVelocity() const { return _transformAttributes._velocity; };
    [[nodiscard]] glm::vec2                  getAcceleration() const { return _transformAttributes._acceleration; };

    void resetForces() { _transformAttributes._acceleration = glm::vec2{0}; };
    void setForcesConfig(ForcesConfig config) { _forcesConfig = config; };
    void setBehaviorConfig(BehaviorConfig config) { _behaviorConfig = config; };

    void addToPosition(glm::vec2 position) { _transformAttributes._position += position; };
    void addToVelocity(glm::vec2 velocity) { _transformAttributes._velocity += velocity; };
    void addToAcceleration(glm::vec2 velocity) { _transformAttributes._velocity += velocity; };

private:
    void addFoodAttraction(FoodProvider&);
    void addObstaclesAvoidance(Obstacles const&);
    void addClassicBoidsForces(std::vector<SingleBoid> const&);

    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const&, double radius) const;

private:
    utils::TransformAttributes _transformAttributes{};
    Species                    _species{};
    BehaviorConfig             _behaviorConfig{};
    ForcesConfig               _forcesConfig{};
};

std::vector<SingleBoid> getNearbyBoidsFromPosition(glm::vec2 const& position, std::vector<SingleBoid> const& boids, double radius);