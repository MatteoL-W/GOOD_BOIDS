#pragma once

#include <p6/p6.h>
#include "Boids/Boid.h"

/// These functions should be call every frame and with every boid in the map.
namespace Utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(Boid const&, ObstaclesManager const&);
glm::vec2 computeFoodAttraction(Boid const&, FoodProvider&, float foodAttractionRadius);

/// Note that std::vector<Boid> should only contains closeBoids.
glm::vec2 computeSeparationForce(Boid const&, std::vector<Boid> const&);
glm::vec2 computeAlignmentForce(Boid const&, std::vector<Boid> const&);
glm::vec2 computeCohesionForce(Boid const&, std::vector<Boid> const&);

}; // namespace utils::boidsForces