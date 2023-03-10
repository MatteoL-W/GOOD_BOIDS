#include "ImGuiHelper.hpp"
#include "p6/p6.h"

namespace BoidsHelper {
void load_boids_helper(Boids& boids, int& numberOfBoids, float& radius)
{
    if (ImGui::CollapsingHeader("Customize boids"))
    {
        ImGui::DragInt("Number of Boids", &numberOfBoids, 1.f, 0, 500);

        if (ImGui::DragFloat("Boids radius", &radius, 0.01f, 0.01f, 0.2f))
            boids.updateRadius(radius);
    }
}

void load_forces_helper(Boids& boids, ForcesConfig& forcesConfig)
{
    if (ImGui::CollapsingHeader("Boids forces"))
    {
        if (ImGui::DragFloat("Separation Radius", &forcesConfig._separation_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Separation Factor", &forcesConfig._avoid_factor, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Alignment Radius", &forcesConfig._alignment_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Alignment Factor", &forcesConfig._matching_factor, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Cohesion Radius", &forcesConfig._cohesion_radius, 0.01f, 0, 1.f)
            || ImGui::DragFloat("Cohesion Factor", &forcesConfig._centering_factor, 0.01f, 0, 1.f))
        {
            boids.updateForcesConfig(forcesConfig);
        }
    }
}

void load_behaviour_helper(Boids& boids, BehaviorConfig& behaviorConfig)
{
    if (ImGui::CollapsingHeader("Boids behaviour"))
    {
        if (ImGui::DragFloat("Boids min speed", &behaviorConfig._minSpeed, 0.01f, 0.f, 5.f)
            || ImGui::DragFloat("Boids max speed", &behaviorConfig._maxSpeed, 0.01f, 0.f, 5.f))
        {
            boids.updateBehaviorConfig(behaviorConfig);
        }
    }
}

void load_shapes_helper(Boids& boids, ShapesType& shape, float& radius)
{
    if (ImGui::CollapsingHeader("Boids Shapes"))
    {
        if (ImGui::Button("Shape : Triangle"))
        {
            shape = Shapes::TwoDimensions::Triangle{radius};
            boids.updateShape(shape);
        }

        if (ImGui::Button("Shape : Circle"))
        {
            shape = Shapes::TwoDimensions::Circle{radius};
            boids.updateShape(shape);
        }

        if (ImGui::Button("Shape : Fish"))
        {
            shape = Shapes::TwoDimensions::Fish{radius};
            boids.updateShape(shape);
        }
    }
}

void load_food_helper(FoodProvider& foodProvider, FoodConfig& foodConfig) {
    if (ImGui::CollapsingHeader("Food Provider")) {
        if (ImGui::DragInt("Number of drops", &foodConfig._drops, 3, 0, 10)
            || ImGui::DragInt("Interval of drop", &foodConfig._providing_interval, 5, 0, 10)
            || ImGui::DragFloat("Boids radius", &foodConfig._radius, 0.1f, 0.01f, 0.2f))
        {
            foodProvider.updateFoodConfig(foodConfig);
        }
    }
}
} // namespace BoidsHelper
