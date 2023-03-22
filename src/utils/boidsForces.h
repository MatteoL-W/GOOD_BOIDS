#pragma once

#include <p6/p6.h>
#include "Boids/SingleBoid.h"

namespace utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(SingleBoid const&, Obstacles const&);
glm::vec2 computeFoodAttraction(SingleBoid const&, FoodProvider&, float foodAttractionRadius);
glm::vec2 computeSeparationForce(SingleBoid const&, std::vector<SingleBoid> const&);
glm::vec2 computeAlignmentForce(SingleBoid const&, std::vector<SingleBoid> const&);
glm::vec2 computeCohesionForce(SingleBoid const&, std::vector<SingleBoid> const&);

}; // namespace utils::boidsForces