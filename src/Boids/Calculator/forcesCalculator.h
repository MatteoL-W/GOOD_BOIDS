#pragma once

#include "Boids/Movement.h"
#include "p6/p6.h"

/// These functions should be call every frame and with every boid in the map.
namespace Boids::Calculator {

glm::vec3 computeObstaclesAvoidance(Movement const&, Features::ObstaclesManager const&, float boidRadius);
glm::vec3 computeFoodAttraction(Movement const&, Features::FoodProvider&, float foodAttractionRadius);

/// Note that std::vector<Boid> should only contains closeBoids.
glm::vec3 computeSeparationForce(Movement const&, std::vector<Movement> const&);
glm::vec3 computeAlignmentForce(Movement const&, std::vector<Movement> const&);
glm::vec3 computeCohesionForce(Movement const&, std::vector<Movement> const&);

} // namespace Boids::Calculator