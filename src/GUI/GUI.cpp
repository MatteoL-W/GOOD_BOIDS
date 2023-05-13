#include "GUI.hpp"
#include <p6/p6.h>

namespace GUI {

void showSpeciesGUI(std::string speciesName, Boids::Species& species)
{
    if (ImGui::BeginTabItem(speciesName.c_str()))
    {
        GUI::showParametersGUI(species);
        GUI::showForcesGUI(species._forcesConfig);
        GUI::showBehaviorGUI(species._behaviorConfig);

        ImGui::EndTabItem();
    }
}

void showParametersGUI(Boids::Species& species)
{
    ImGui::SeparatorText("Parameters");

    ImGui::DragInt("Number of Boids", &species._quantity, 1.f, 0, 500);
}

void showForcesGUI(Boids::ForcesConfig& forcesConfig)
{
    ImGui::SeparatorText("Boids forces");

    if (ImGui::DragFloat("Separation Radius", &forcesConfig._separationRadius, 0.01f, 0, 10.f)
        || ImGui::DragFloat("Separation Factor", &forcesConfig._separationFactor, 0.01f, 0, 10.f)
        || ImGui::DragFloat("Alignment Radius", &forcesConfig._alignmentRadius, 0.01f, 0, 10.f)
        || ImGui::DragFloat("Alignment Factor", &forcesConfig._alignmentFactor, 0.01f, 0, 10.f)
        || ImGui::DragFloat("Cohesion Radius", &forcesConfig._cohesionRadius, 0.01f, 0, 10.f)
        || ImGui::DragFloat("Cohesion Factor", &forcesConfig._cohesionFactor, 0.01f, 0, 10.f))
    {
    }
}

void showBehaviorGUI(Boids::BehaviorConfig& behaviorConfig)
{
    ImGui::SeparatorText("Boids behaviour");

    if (ImGui::DragFloat("Boids min speed", &behaviorConfig._minSpeed, .001f, 0.f, 2.f)
        || ImGui::DragFloat("Boids max speed", &behaviorConfig._maxSpeed, .001f, 0.f, 5.f)
        || ImGui::DragFloat("Food attraction radius", &behaviorConfig._foodAttractionRadius, 0.01f, 0.f, 5.f))
    {
    }
}

void showFoodGUI(Features::FoodProvider& foodProvider)
{
    ImGui::SeparatorText("Food Provider");

    if (ImGui::DragInt("Number of drops", &foodProvider.getConfig()._drops, 3, 0, 10)
        || ImGui::DragInt("Interval of drop", &foodProvider.getConfig()._providing_interval, 5, 0, 30)
        || ImGui::DragFloat("Food radius", &foodProvider.getConfig()._radius, 0.1f, 0.01f, 0.2f))
    {
    }

    ImGui::Spacing();
}

void showCameraGUI()
{
    ImGui::SeparatorText("Camera");

    auto cameraManager = Camera::getCameraInstance();
    if (ImGui::Button("Third Person"))
    {
        Camera::CameraType newCam = Camera::ThirdPerson{};
        cameraManager.changeCamera(newCam);
    }

    if (ImGui::Button("First Person"))
    {
        Camera::CameraType newCam = Camera::FirstPerson{};
        cameraManager.changeCamera(newCam);
    }

    ImGui::Spacing();
}

} // namespace GUI
