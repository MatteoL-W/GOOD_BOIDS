#pragma once

#include "Boids/Boid.h"
#include "Boids/Manager.h"
#include "Features/FoodProvider.h"

// ToDo "separator text" pour imgui

namespace GUI {

void showSpeciesGUI(std::string speciesName, Boids::Species&);

void showParametersGUI(Boids::Species&);
void showForcesGUI(Boids::ForcesConfig&);
void showBehaviorGUI(Boids::BehaviorConfig&);
// ToDo : showShapeGUI ? avec radius ?
void showFoodGUI(Features::FoodProvider&);

} // namespace GUI