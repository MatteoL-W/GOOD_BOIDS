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
    ImGui::Text("Parameters");

    ImGui::DragInt("Number of Boids", &species._quantity, 1.f, 0, 500);
}

void showForcesGUI(Boids::ForcesConfig& forcesConfig)
{
    ImGui::Text("Boids forces");

    if (ImGui::DragFloat("Separation Radius", &forcesConfig._separationRadius, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Separation Factor", &forcesConfig._separationFactor, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Alignment Radius", &forcesConfig._alignmentRadius, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Alignment Factor", &forcesConfig._alignmentFactor, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Cohesion Radius", &forcesConfig._cohesionRadius, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Cohesion Factor", &forcesConfig._cohesionFactor, 0.01f, 0.f, 10.f)
        || ImGui::DragFloat("Turn factor", &forcesConfig._turnFactor, 0.1f, 0.f, 2.f))
    {
    }
}

void showBehaviorGUI(Boids::BehaviorConfig& behaviorConfig)
{
    ImGui::Text("Boids behaviour");

    if (ImGui::DragFloat("Boids min speed", &behaviorConfig._minSpeed, .001f, 0.f, 2.f)
        || ImGui::DragFloat("Boids max speed", &behaviorConfig._maxSpeed, .001f, 0.f, 5.f)
        || ImGui::DragFloat("Food attraction radius", &behaviorConfig._foodAttractionRadius, 0.01f, 0.f, 5.f))
    {
    }
}

void showFoodGUI(Features::FoodConfig& foodConfig)
{
    ImGui::SeparatorText("Food Provider");

    if (ImGui::DragInt("Number of food drops", &foodConfig._drops, 3, 0, 10)
        || ImGui::DragInt("Interval of food drop", &foodConfig._providingInterval, 5, 0, 30)
        || ImGui::DragFloat("Food radius", &foodConfig._radius, 0.1f, 0.1f, 0.9f))
    {
    }

    ImGui::Spacing();
}

void showObstacleGUI(Features::ObstaclesConfig& config) {
    ImGui::SeparatorText("Obstacles Manager");

    if (ImGui::DragInt("Number of obstacles drops", &config._drops, 3, 0, 10)
        || ImGui::DragInt("Interval of obstacles drop", &config._providingInterval, 5, 0, 30)
        || ImGui::DragFloat("Falling factor", &config._fallingFactor, 0.01f, 0.01f, 0.05f))
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

void showDirectionalLightGUI(std::optional<Rendering::Lights::Directional>& light)
{
    if (!light.has_value())
        return;

    ImGui::SeparatorText("Directional light");

    ImGui::SliderFloat3("Direction", glm::value_ptr(light->getDirection()), -10.0f, 10.0f);
    ImGui::SliderFloat3("Position", glm::value_ptr(light->getPosition()), -10.0f, 10.0f);
    ImGui::SliderFloat3("Color", glm::value_ptr(light->getColor()), 0.f, 1.0f);
    ImGui::SliderFloat("Ambient", &light->getIntensity()._ambient, 0.f, 1.f);
    ImGui::SliderFloat("Diffuse", &light->getIntensity()._diffuse, 0.f, 1.f);
    ImGui::SliderFloat("Specular", &light->getIntensity()._specular, 0.f, 1.f);

    ImGui::Spacing();
}

void showPointLightsGUI(std::vector<Rendering::Lights::Point>& lights)
{
    ImGui::SeparatorText("Point lights");

    if (lights.size() < 10 && ImGui::Button("Add light"))
    {
        auto newLight = Rendering::Lights::Point{{}, {.1f, .2f, .3f}, {1.f, 1.f, 1.f}, 1.f, .09f, .032f};
        lights.push_back(newLight);
    }

    if (lights.empty())
        return;

    for (size_t i = 0; i < lights.size(); i++)
    {
        std::string const title = "Point light n°" + std::to_string(i);
        if (ImGui::CollapsingHeader(title.c_str()))
        {
            ImGui::SliderFloat3(("PL Position " + std::to_string(i)).c_str(), glm::value_ptr(lights[i].getPosition()), -10.0f, 10.0f);
            ImGui::SliderFloat3(("PL Color " + std::to_string(i)).c_str(), glm::value_ptr(lights[i].getColor()), 0.f, 1.0f);
            ImGui::SliderFloat(("PL Ambient " + std::to_string(i)).c_str(), &lights[i].getIntensity()._ambient, 0.f, 1.f);
            ImGui::SliderFloat(("PL Diffuse " + std::to_string(i)).c_str(), &lights[i].getIntensity()._diffuse, 0.f, 1.f);
            ImGui::SliderFloat(("PL Specular " + std::to_string(i)).c_str(), &lights[i].getIntensity()._specular, 0.f, 1.f);
            ImGui::SliderFloat(("PL Constant " + std::to_string(i)).c_str(), &lights[i].getConstant(), 0.f, 1.f);
            ImGui::SliderFloat(("PL Linear " + std::to_string(i)).c_str(), &lights[i].getLinear(), 0.f, 1.f);
            ImGui::SliderFloat(("PL Quadratic " + std::to_string(i)).c_str(), &lights[i].getQuadratic(), 0.f, 1.f);
        }
    }

    ImGui::Spacing();
}

} // namespace GUI
