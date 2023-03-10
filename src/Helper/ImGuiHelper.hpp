#pragma once

#include "Boids/Boids.h"
#include "Boids/SingleBoid.h"
#include "Food/FoodProvider.h"

namespace BoidsHelper {
void load_boids_helper(Boids&, int& numberOfBoids, float& radius);
void load_forces_helper(Boids&, ForcesConfig&);
void load_behaviour_helper(Boids&, BehaviorConfig&);
void load_shapes_helper(Boids&, ShapesType&, float& radius);
void load_food_helper(FoodProvider&, FoodConfig&);
} // namespace BoidsHelper