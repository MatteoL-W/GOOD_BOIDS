#pragma once

#include "Obstacles.h"
#include "p6/p6.h"

struct Movement {
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};
};

struct Config {
    float _radius            = 0.05f;
    float _minSpeed          = .5f;
    float _maxSpeed          = 2.f;
    float _separation_radius = _radius * 2;
    float _avoid_factor      = .1f;
    float _alignment_radius  = _radius * 2;
    float _matching_factor   = .1f;
    float _cohesion_radius   = _radius * 2;
    float _centering_factor  = .1f;
};

class SingleBoid {
public:
    explicit SingleBoid(Movement const& movement, Config const& config);
    void update(std::vector<SingleBoid> const& boids, Obstacles const& obstacles);
    void resetForces() { _movement._acceleration = glm::vec2{0}; };

    [[nodiscard]] glm::vec2 getPosition() const { return _movement._position; };
    [[nodiscard]] glm::vec2 getVelocity() const { return _movement._velocity * glm::vec2(0.01f); };
    [[nodiscard]] glm::vec2 getAcceleration() const { return _movement._acceleration; };
    [[nodiscard]] float     getRadius() const { return _config._radius; };

    void setConfig(Config config) { _config = config; };

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
    Movement _movement{};
    Config   _config{};
};
