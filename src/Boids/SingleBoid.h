#pragma once

#include <p6/p6.h>
#include "Food/FoodProvider.h"
#include "Obstacles/Obstacles.h"
#include "Shapes/2D.h"
#include "utils/TransformAttributes.h"

struct BehaviorConfig {
    float _minSpeed             = .005f;
    float _maxSpeed             = .2f;
    float _foodAttractionRadius = 0.3f;
};

struct ForcesConfig {
    float _separationRadius = .1f;
    float _avoidFactor      = .1f;
    float _alignmentRadius  = .2f;
    float _matchingFactor   = .1f;
    float _cohesionRadius   = .1f;
    float _centeringFactor  = .1f;
};

class SingleBoid {
public:
    explicit SingleBoid(utils::TransformAttributes const&, ShapesType const&, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<SingleBoid> const&, Obstacles const&, FoodProvider&);
    void draw(p6::Context&);

    [[nodiscard]] utils::TransformAttributes getTransformAttributes() const { return _transformAttributes; };
    [[nodiscard]] glm::vec2                  getPosition() const { return _transformAttributes._position; };
    [[nodiscard]] glm::vec2                  getVelocity() const { return _transformAttributes._velocity; };
    [[nodiscard]] glm::vec2                  getAcceleration() const { return _transformAttributes._acceleration; };
    [[nodiscard]] ShapesType const&          getShape() const { return _shape; };

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

    [[nodiscard]] std::vector<SingleBoid> getNearbyAndSameBoids(std::vector<SingleBoid> const& boids, double radius) const;

private:
    utils::TransformAttributes _transformAttributes{};
    ShapesType                 _shape{};
    BehaviorConfig             _behaviorConfig{};
    ForcesConfig               _forcesConfig{};
};

std::vector<SingleBoid> getNearbyBoidsFromPosition(glm::vec2 const& position, std::vector<SingleBoid> const& boids, double radius, ShapesType const& shape);
