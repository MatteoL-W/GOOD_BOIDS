#pragma once

#include <p6/p6.h>
#include "Boids/SingleBoid.h"

namespace utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(SingleBoid, Obstacles const&);
glm::vec2 computeFoodAttraction(SingleBoid, FoodProvider&, float foodAttractionRadius);
glm::vec2 computeSeparationForce(SingleBoid, std::vector<SingleBoid> const&);
glm::vec2 computeAlignmentForce(SingleBoid, std::vector<SingleBoid> const&);
glm::vec2 computeCohesionForce(SingleBoid, std::vector<SingleBoid> const&);

}; // namespace utils::boidsForces