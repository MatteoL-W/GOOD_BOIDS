#pragma once

#include "Boids/Boid.h"
#include "Boids/Manager.h"
#include "Features/FoodProvider.h"

// ToDo "separator text" pour imgui

namespace GUI {

void showSpeciesGUI(std::string speciesName, Boids::Species&, Boids::Manager&);

void showParametersGUI(Boids::Species&);
void showForcesGUI(Boids::Manager&, unsigned int speciesId, Boids::ForcesConfig&);
void showBehaviorGUI(Boids::Manager&, unsigned int speciesId, Boids::BehaviorConfig&);
// ToDo : showShapeGUI ? avec radius ?
void showFoodGUI(Features::FoodProvider&);

} // namespace GUI