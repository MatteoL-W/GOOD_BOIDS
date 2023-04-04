#pragma once

#include "Boids/Boid.h"
#include "Boids/BoidsManager.h"
#include "Food/FoodProvider.h"

// ToDo "separator text" pour imgui

namespace GUI {

void showSpeciesGUI(std::string speciesName, Species&, BoidsManager&);

void showParametersGUI(Species&);
void showForcesGUI(BoidsManager&, unsigned int speciesId, ForcesConfig&);
void showBehaviorGUI(BoidsManager&, unsigned int speciesId, BehaviorConfig&);
// ToDo : showShapeGUI ? avec radius ?
void showFoodGUI(FoodProvider&);

} // namespace GUI