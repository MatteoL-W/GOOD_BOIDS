#include "boidsForces.h"

namespace utils::boidsForces {

glm::vec2 computeObstaclesAvoidance(SingleBoid boid, Obstacles const& obstacles)
{
    auto force = glm::vec2{};

    for (auto const& obstacle : obstacles.getAll())
    {
        const float distanceToObstacle = glm::distance(obstacle._position, boid.getPosition());
        const float avoidanceRadius    = obstacle._radius * 2.f;
        if (distanceToObstacle > avoidanceRadius)
            continue;

        // Calculate a avoidanceStrength value based on how close the boid is to the obstacle
        const float avoidanceStrength           = glm::clamp((avoidanceRadius - distanceToObstacle) / avoidanceRadius, 0.0f, 1.0f) / 2.f;
        const auto  directionToObstacle         = glm::normalize(boid.getPosition() - obstacle._position);
        const auto  fartherPositionFromObstacle = boid.getPosition() + directionToObstacle * avoidanceRadius;
        const auto  avoidanceVelocity           = glm::normalize(fartherPositionFromObstacle - boid.getPosition());
        const auto  steeringForceFromAvoidance  = avoidanceVelocity - boid.getVelocity();

        force += glm::normalize(steeringForceFromAvoidance + directionToObstacle * avoidanceStrength) * avoidanceStrength;
    }

    return force;
}

glm::vec2 computeFoodAttraction(SingleBoid boid, FoodProvider& foodProvider, float foodAttractionRadius)
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

glm::vec2 computeSeparationForce(SingleBoid boid, std::vector<SingleBoid> const& closeBoids)
{
    auto force = glm::vec2{};

    for (auto const& closeMember : closeBoids)
        force += glm::normalize(boid.getPosition() - closeMember.getPosition()) / glm::distance(boid.getPosition(), closeMember.getPosition());

    return force;
}

glm::vec2 computeAlignmentForce(SingleBoid boid, std::vector<SingleBoid> const& closeBoids)
{
    if (closeBoids.empty())
        return glm::vec2{};

    auto averageVelocity = glm::vec2{};
    for (auto const& closeMember : closeBoids)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeBoids.size());
    return averageVelocity - boid.getVelocity();
}

glm::vec2 computeCohesionForce(SingleBoid boid, std::vector<SingleBoid> const& closeBoids)
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