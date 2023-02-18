#pragma once

#include "p6/p6.h"

class SingleBoid {
public:
    explicit SingleBoid(glm::vec2 const& position, float const& radius);
    void update(p6::Context& ctx, const std::vector<SingleBoid>& boids);
    void draw(p6::Context& ctx);

private:
    void                                  applySteeringForces(const std::vector<SingleBoid>& boids);
    void                                  keepBoidInTheScreen(const p6::Context& ctx);
    [[nodiscard]] std::vector<SingleBoid> getNearbyBoids(std::vector<SingleBoid> const& boids, double radius);
    [[nodiscard]] glm::vec2               computeSeparationForce(const std::vector<SingleBoid>& boids);
    [[nodiscard]] glm::vec2               computeAlignmentForce(const std::vector<SingleBoid>& boids);
    [[nodiscard]] glm::vec2               computeCohesionForce(const std::vector<SingleBoid>& boids);

private:
    // ToDo : Struct this
    glm::vec2 _position{};
    glm::vec2 _velocity{};
    glm::vec2 _acceleration{};

    float _maxSpeed = 2.f;
    float _radius;
};
