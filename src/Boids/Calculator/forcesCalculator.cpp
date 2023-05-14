#include "forcesCalculator.h"

namespace Boids::Calculator {

glm::vec3 computeObstaclesAvoidance(Movement const& boid, Features::ObstaclesManager const& obstacles, float boidRadius)
{
    auto force = glm::vec3{};

    for (auto const& obstacle : obstacles.getObstacles())
    {
        auto toObstacle      = obstacle._position - boid.getPosition();
        auto distance        = glm::length(toObstacle);
        auto avoidanceRadius = boidRadius + obstacle._radius * 2;

        if (distance > avoidanceRadius)
            continue;

        if (distance < obstacle._radius)
        {
            /// The boid is inside the obstacle, push it away drastically
            force -= glm::normalize(toObstacle);
            continue;
        }

        /// Smoother bend when the obstacle is pretty close
        auto tangentPoint         = boid.getPosition() + glm::normalize(toObstacle) * obstacle._radius;
        auto awayFromTangentForce = boid.getPosition() - tangentPoint;
        auto distanceFactor       = (avoidanceRadius - distance) / avoidanceRadius;
        auto smoothFactor         = glm::smoothstep(0.0f, 1.0f, distanceFactor);
        awayFromTangentForce *= smoothFactor;

        force += awayFromTangentForce;
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
        averagePosition += glm::normalize(closeMember.getPosition());

    averagePosition /= static_cast<float>(closeBoids.size());
    return averagePosition - boid.getPosition();
}

}; // namespace Boids::Calculator