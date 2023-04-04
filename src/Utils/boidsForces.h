#pragma once

#include <p6/p6.h>
#include "Boids/BoidMovement.h"

/// These functions should be call every frame and with every boid in the map.
namespace Utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(BoidMovement const&, ObstaclesManager const&, float boidRadius);
glm::vec2 computeFoodAttraction(BoidMovement const&, FoodProvider&, float foodAttractionRadius);

/// Note that std::vector<Boid> should only contains closeBoids.
glm::vec2 computeSeparationForce(BoidMovement const&, std::vector<BoidMovement> const&);
glm::vec2 computeAlignmentForce(BoidMovement const&, std::vector<BoidMovement> const&);
glm::vec2 computeCohesionForce(BoidMovement const&, std::vector<BoidMovement> const&);

}  // namespace Utils::boidsForces