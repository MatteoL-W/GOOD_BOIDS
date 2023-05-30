#include "forcesCalculator.h"

namespace Boids::Calculator {

glm::vec3 computeObstaclesAvoidance(const Movement& boid, const Features::ObstaclesManager& obstacles, float boidRadius)
{
    glm::vec3 force;

    for (const auto& obstacle : obstacles.getObstacles())
    {
        auto const  direction    = obstacle._position - boid.getPosition();
        float const distance     = glm::length(direction);
        float const sumOfRadii   = obstacle._radius + boidRadius;
        float const safeDistance = sumOfRadii * 2.f; // Define a safe distance threshold

        if (distance < safeDistance)
        {
            // The boid is too close to the obstacle, calculate the desired force
            auto const avoidanceForce = glm::normalize(direction) * (safeDistance - distance);
            force += avoidanceForce;
        }
    }

    return force;
}

glm::vec3 computeFoodAttraction(Movement const& boid, Features::FoodProvider& foodProvider, float foodAttractionRadius)
{
    auto const& allFood = foodProvider.getFood();
    if (allFood.empty())
        return glm::vec3{};

    auto closestFood = allFood.begin();

    float minDistance = glm::distance(boid.getPosition(), *closestFood);
    for (auto food = allFood.begin(); food != allFood.end(); ++food)
    {
        const float distance = glm::distance(boid.getPosition(), *food);
        if (distance < minDistance)
        {
            closestFood = food;
            minDistance = distance;
        }
    }

    if (foodAttractionRadius < minDistance)
        return glm::vec3{};

    auto const foodAttraction = glm::normalize(*closestFood - boid.getPosition());

    if (minDistance < foodProvider.getFoodRadius())
        foodProvider.erase(closestFood);

    return foodAttraction;
}

glm::vec3 computeSeparationForce(Movement const& boid, std::vector<Movement> const& closeBoids)
{
    auto force = glm::vec3{};

    for (auto const& closeMember : closeBoids)
        force += glm::normalize(boid.getPosition() - closeMember.getPosition()) / glm::distance(boid.getPosition(), closeMember.getPosition());

    return force - boid.getVelocity();
}

glm::vec3 computeAlignmentForce(Movement const& boid, std::vector<Movement> const& closeBoids)
{
    if (closeBoids.empty())
        return glm::vec3{};

    auto averageVelocity = glm::vec3{};
    for (auto const& closeMember : closeBoids)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeBoids.size());
    return averageVelocity - boid.getVelocity();
}

glm::vec3 computeCohesionForce(Movement const& boid, std::vector<Movement> const& closeBoids)
{
    if (closeBoids.empty())
        return glm::vec3{};

    auto averagePosition = glm::vec3{};
    for (auto const& closeMember : closeBoids)
        averagePosition += closeMember.getPosition();

    averagePosition /= static_cast<float>(closeBoids.size());
    return averagePosition - boid.getPosition();
}

}; // namespace Boids::Calculator