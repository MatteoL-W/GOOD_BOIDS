#pragma once

#include "p6/p6.h"

struct Movement {
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};
};

struct Config {
    float _radius            = 0.05f;
    float _maxSpeed          = 2.f;
    float _separation_radius = _radius * 2;
    float _alignment_radius  = _radius * 4;
    float _cohesion_radius   = _radius * 2;
};

class SingleBoid {
public:
    explicit SingleBoid(Movement const& movement, Config const& config);
    void update(p6::Context& ctx, std::vector<SingleBoid> const& boids);
    void draw(p6::Context& ctx) const;

    [[nodiscard]] glm::vec2 getPosition() const { return _movement._position; };
    [[nodiscard]] glm::vec2 getVelocity() const { return _movement._velocity; };
    [[nodiscard]] glm::vec2 getAcceleration() const { return _movement._acceleration; };
    [[nodiscard]] float     getRadius() const { return _config._radius; };

    void setConfig(Config config) { _config = config; };
    void setAcceleration(glm::vec2 acceleration) { _movement._acceleration = acceleration; };

    void addToPosition(glm::vec2 position) { _movement._position += position; };
    void addToVelocity(glm::vec2 velocity) { _movement._velocity += velocity; };
    void addToAcceleration(glm::vec2 velocity) { _movement._velocity += velocity; };

private:
    void                                  applySteeringForces(std::vector<SingleBoid> const& boids);
    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const;
    [[nodiscard]] glm::vec2               computeSeparationForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeAlignmentForce(std::vector<SingleBoid> const& boids) const;
    [[nodiscard]] glm::vec2               computeCohesionForce(std::vector<SingleBoid> const& boids) const;
    void                                  keepInTheScreen(p6::Context const& ctx);

private:
    Movement _movement{};
    Config   _config{};
};
