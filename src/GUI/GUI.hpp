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


void showFoodGUI(Features::FoodConfig&);
void showObstacleGUI(Features::ObstaclesConfig&);
void showCameraGUI();
void showDirectionalLightGUI(std::optional<Rendering::Lights::Directional>&);
void showPointLightsGUI(std::vector<Rendering::Lights::Point>&);

} // namespace GUI