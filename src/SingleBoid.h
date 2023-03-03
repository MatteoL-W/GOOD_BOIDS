#pragma once

#include "Obstacles.h"
#include "p6/p6.h"

struct Movement {
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};
};

struct BehaviorConfig {
    float _minSpeed = .5f;
    float _maxSpeed = 2.f;
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
    explicit SingleBoid(Movement const&, float const& radius, BehaviorConfig const&, ForcesConfig const&);
    void update(std::vector<SingleBoid> const& boids, Obstacles const&);
    void resetForces() { _movement._acceleration = glm::vec2{0}; };

    [[nodiscard]] glm::vec2 getPosition() const { return _movement._position; };
    [[nodiscard]] glm::vec2 getVelocity() const { return _movement._velocity * glm::vec2(0.01f); };
    [[nodiscard]] glm::vec2 getAcceleration() const { return _movement._acceleration; };
    [[nodiscard]] float     getRadius() const { return _radius; };

    void setRadius(float radius) { _radius = radius; };
    void setForcesConfig(ForcesConfig config) { _forcesConfig = config; };
    void setBehaviorConfig(BehaviorConfig config) { _behaviorConfig = config; };

    void addToPosition(glm::vec2 position) { _movement._position += position; };
    void addToVelocity(glm::vec2 velocity) { _movement._velocity += velocity; };
    void addToAcceleration(glm::vec2 velocity) { _movement._velocity += velocity; };

private:
    void addObstaclesForce(Obstacles const& obstacles);
    void addClassicBoidsForces(std::vector<SingleBoid> const& boids);

    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const;
    [[nodiscard]] glm::vec2               computeObstaclesForce(Obstacles const& obstacles) const;
    [[nodiscard]] glm::vec2               computeSeparationForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeAlignmentForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeCohesionForce(std::vector<SingleBoid> const& boids) const;

private:
    Movement       _movement{};
    float          _radius = 0.05f;
    BehaviorConfig _behaviorConfig{};
    ForcesConfig   _forcesConfig{};
};
