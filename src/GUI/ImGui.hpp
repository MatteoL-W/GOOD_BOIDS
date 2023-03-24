#pragma once

#include "Boids/Boids.h"
#include "Boids/SingleBoid.h"
#include "Food/FoodProvider.h"

namespace GUI {

void showSpeciesGUI(std::string speciesName, Species&, Boids&);

void showParametersGUI(Species&);
void showForcesGUI(Boids&, ForcesConfig&);
void showBehaviorGUI(Boids&, BehaviorConfig&);
// ToDo : showShapeGUI ? avec radius ?
void showFoodGUI(FoodProvider&);

} // namespace GUI