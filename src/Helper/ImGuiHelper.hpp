#pragma once

#include "Boids/Boids.h"
#include "Boids/SingleBoid.h"

namespace BoidsHelper {
void load_boids_helper(Boids& boids, int& numberOfBoids, float& radius);
void load_forces_helper(Boids& boids, ForcesConfig& forcesConfig);
void load_behaviour_helper(Boids& boids, BehaviorConfig& behaviorConfig);
void load_shapes_helper(Boids& boids, ShapesType& shape, float& radius);
} // namespace BoidsHelper