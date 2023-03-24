#pragma once

#include <p6/p6.h>
#include "Food/FoodProvider.h"
#include "Obstacles/ObstaclesManager.h"
#include "Shapes/2D.h"
#include "utils/TransformAttributes.h"

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
};

class SingleBoid {
public:
    explicit SingleBoid(std::string species, utils::TransformAttributes const&, ShapesType const&, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<SingleBoid> const&, ObstaclesManager const&, FoodProvider&);
    void draw(p6::Context&);

    [[nodiscard]] std::string                getSpecies() const { return _species; };
    [[nodiscard]] utils::TransformAttributes getTransformAttributes() const { return _transformAttributes; };
    [[nodiscard]] glm::vec2                  getPosition() const { return _transformAttributes._position; };
    [[nodiscard]] glm::vec2                  getVelocity() const { return _transformAttributes._velocity; };
    [[nodiscard]] glm::vec2                  getAcceleration() const { return _transformAttributes._acceleration; };
    [[nodiscard]] ShapesType const&          getShape() const { return _shape; };
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
    void addClassicBoidsForces(std::vector<SingleBoid> const&);

    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const;
    [[nodiscard]] std::vector<SingleBoid> getNearbyAndSameBoids(std::vector<SingleBoid> const& boids, double radius) const;

private:
    std::string                _species;
    utils::TransformAttributes _transformAttributes{};
    ShapesType                 _shape{};
    BehaviorConfig             _behaviorConfig{};
    ForcesConfig               _forcesConfig{};
};

std::vector<SingleBoid> getNearbyBoidsFromBoid(
    SingleBoid const&                 scannedBoid,
    std::vector<SingleBoid> const&    closeShape,
    double                            maxDistance,
    std::optional<std::string> const& species
);
