#pragma once

#include <p6/p6.h>
#include "Food/FoodProvider.h"
#include "Obstacles/Obstacles.h"

struct Movement {
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};
};

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
    explicit SingleBoid(Movement const&, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<SingleBoid> const&, Obstacles const&, FoodProvider&);
    void resetForces() { _movement._acceleration = glm::vec2{0}; };

    [[nodiscard]] Movement  getMovement() const { return _movement; };
    [[nodiscard]] glm::vec2 getPosition() const { return _movement._position; };
    [[nodiscard]] glm::vec2 getVelocity() const { return _movement._velocity; };
    [[nodiscard]] glm::vec2 getAcceleration() const { return _movement._acceleration; };

    void setForcesConfig(ForcesConfig config) { _forcesConfig = config; };
    void setBehaviorConfig(BehaviorConfig config) { _behaviorConfig = config; };

    void addToPosition(glm::vec2 position) { _movement._position += position; };
    void addToVelocity(glm::vec2 velocity) { _movement._velocity += velocity; };
    void addToAcceleration(glm::vec2 velocity) { _movement._velocity += velocity; };

private:
    void addFoodAttraction(FoodProvider&);
    void addObstaclesAvoidance(Obstacles const&);
    void addClassicBoidsForces(std::vector<SingleBoid> const& boids);

    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const;
    [[nodiscard]] glm::vec2               computeFoodAttraction(FoodProvider&) const;
    [[nodiscard]] glm::vec2               computeObstaclesAvoidance(Obstacles const&) const;
    [[nodiscard]] glm::vec2               computeSeparationForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeAlignmentForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeCohesionForce(std::vector<SingleBoid> const& boids) const;

private:
    Movement       _movement{};
    BehaviorConfig _behaviorConfig{};
    ForcesConfig   _forcesConfig{};
};

std::vector<SingleBoid> getNearbyBoidsFromPosition(glm::vec2 const& position, std::vector<SingleBoid> const& boids, double radius);