#pragma once

#include <p6/p6.h>
#include "Boids/BoidMovement.h"

/// These functions should be call every frame and with every boid in the map.
namespace Utils::boidsForces {

glm::vec3 computeObstaclesAvoidance(BoidMovement const&, Features::ObstaclesManager const&, float boidRadius);
glm::vec3 computeFoodAttraction(BoidMovement const&, Features::FoodProvider&, float foodAttractionRadius);

/// Note that std::vector<Boid> should only contains closeBoids.
glm::vec3 computeSeparationForce(BoidMovement const&, std::vector<BoidMovement> const&);
glm::vec3 computeAlignmentForce(BoidMovement const&, std::vector<BoidMovement> const&);
glm::vec3 computeCohesionForce(BoidMovement const&, std::vector<BoidMovement> const&);

} // namespace Utils::boidsForces