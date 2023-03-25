#include "boidsForces.h"

namespace utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(Boid const& boid, ObstaclesManager const& obstacles)
{
    auto force = glm::vec2{};

    // ToDo : It sometimes overflow when the flock is big
    for (auto const& obstacle : obstacles.getObstacles())
    {
        auto toObstacle      = obstacle._position - boid.getPosition();
        auto distance        = glm::length(toObstacle);
        auto avoidanceRadius = boid.getRadius() + obstacle._radius * 2;

        if (distance > avoidanceRadius)
            continue;

        if (distance < obstacle._radius) {
            // The boid is inside the obstacle, push it away drastically
            force -= glm::normalize(toObstacle);
            continue;
        }

        // Smoother bend when the obstacle is pretty close
        auto tangentPoint         = boid.getPosition() + glm::normalize(toObstacle) * obstacle._radius;
        auto awayFromTangentForce = boid.getPosition() - tangentPoint;
        auto distanceFactor       = (avoidanceRadius - distance) / avoidanceRadius;
        auto smoothFactor         = glm::smoothstep(0.0f, 1.0f, distanceFactor);
        awayFromTangentForce *= smoothFactor;

        force += awayFromTangentForce;
    }

    return force;
}

glm::vec2 computeFoodAttraction(Boid const& boid, FoodProvider& foodProvider, float foodAttractionRadius)
{
    auto const& allFood = foodProvider.getFood();
    if (allFood.empty())
        return glm::vec2{};

    auto closestFood = allFood.begin(); // initialize to the first food item

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
        return glm::vec2{};

    if (minDistance < foodProvider.getFoodRadius())
        foodProvider.erase(closestFood);

    return glm::normalize(*closestFood - boid.getPosition()); //  * _config._food_attraction_strength;
}

glm::vec2 computeSeparationForce(Boid const& boid, std::vector<Boid> const& closeBoids)
{
    auto force = glm::vec2{};

    for (auto const& closeMember : closeBoids)
        force += glm::normalize(boid.getPosition() - closeMember.getPosition()) / glm::distance(boid.getPosition(), closeMember.getPosition());

    return force - boid.getVelocity();
}

glm::vec2 computeAlignmentForce(Boid const& boid, std::vector<Boid> const& closeBoids)
{
    if (closeBoids.empty())
        return glm::vec2{};

    auto averageVelocity = glm::vec2{};
    for (auto const& closeMember : closeBoids)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeBoids.size());
    return averageVelocity - boid.getVelocity();
}

glm::vec2 computeCohesionForce(Boid const& boid, std::vector<Boid> const& closeBoids)
{
    if (closeBoids.empty())
        return glm::vec2{};

    auto averagePosition = glm::vec2{};
    for (auto const& closeMember : closeBoids)
        averagePosition += glm::normalize(closeMember.getPosition());

    averagePosition /= static_cast<float>(closeBoids.size());
    return averagePosition - boid.getPosition();
}

}; // namespace utils::boidsForces