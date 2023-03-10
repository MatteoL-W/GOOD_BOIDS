#include "SingleBoid.h"
#include "utils/vec.hpp"

SingleBoid::SingleBoid(TransformAttributes const& transformAttributes, ShapesType const& shapesType, BehaviorConfig const& behaviorConfig, ForcesConfig const& forcesConfig)
    : _transformAttributes(transformAttributes), _shape(shapesType), _behaviorConfig(behaviorConfig), _forcesConfig(forcesConfig)
{}

void SingleBoid::update(std::vector<SingleBoid> const& boids, Obstacles const& obstacles, FoodProvider& foodProvider)
{
    addFoodAttraction(foodProvider);
    addObstaclesAvoidance(obstacles);
    addClassicBoidsForces(boids);

    addToVelocity(getAcceleration());
    utils::vec::constrain(_transformAttributes._velocity, _behaviorConfig._minSpeed, _behaviorConfig._maxSpeed);

    addToPosition(getVelocity());
    resetForces();
}

void SingleBoid::addFoodAttraction(FoodProvider& foodProvider)
{
    addToAcceleration(computeFoodAttraction(foodProvider));
}

void SingleBoid::addObstaclesAvoidance(Obstacles const& obstacles)
{
    addToAcceleration(computeObstaclesAvoidance(obstacles));
}

void SingleBoid::addClassicBoidsForces(std::vector<SingleBoid> const& boids)
{
    addToAcceleration(computeSeparationForce(boids));
    addToAcceleration(computeAlignmentForce(boids));
    addToAcceleration(computeCohesionForce(boids));
}

glm::vec2 SingleBoid::computeFoodAttraction(FoodProvider& foodProvider) const
{
    auto const& allFood = foodProvider.getFood();
    if (allFood.empty())
        return glm::vec2{};

    auto closestFood = allFood.begin(); // initialize to the first food item

    float minDistance = glm::distance(getPosition(), *closestFood);
    for (auto food = allFood.begin(); food != allFood.end(); ++food)
    {
        const float distance = glm::distance(getPosition(), *food);
        if (distance < minDistance)
        {
            closestFood = food;
            minDistance = distance;
        }
    }

    if (_behaviorConfig._food_attraction_radius < minDistance)
        return glm::vec2{};

    if (minDistance < foodProvider.getFoodRadius())
        foodProvider.erase(closestFood);

    return glm::normalize(*closestFood - getPosition()); //  * _config._food_attraction_strength;
}

glm::vec2 SingleBoid::computeObstaclesAvoidance(Obstacles const& obstacles) const
{
    // ToDo : ImGui
    auto force = glm::vec2{};

    for (auto const& obstacle : obstacles.getAll())
    {
        const float distanceToObstacle = glm::distance(obstacle._position, getPosition());
        const float avoidanceRadius    = obstacle._radius * 2.f;
        if (distanceToObstacle > avoidanceRadius)
            continue;

        // Calculate a avoidanceStrength value based on how close the boid is to the obstacle
        const float avoidanceStrength           = glm::clamp((avoidanceRadius - distanceToObstacle) / avoidanceRadius, 0.0f, 1.0f);
        const auto  directionToObstacle         = glm::normalize(getPosition() - obstacle._position);
        const auto  fartherPositionFromObstacle = getPosition() + directionToObstacle * avoidanceRadius;
        const auto  avoidanceVelocity           = glm::normalize(fartherPositionFromObstacle - getPosition());
        const auto  steeringForceFromAvoidance  = avoidanceVelocity - getVelocity();

        force += glm::normalize(steeringForceFromAvoidance + directionToObstacle * avoidanceStrength) * avoidanceStrength;
    }

    return force;
}

glm::vec2 SingleBoid::computeSeparationForce(std::vector<SingleBoid> const& boids) const
{
    auto force = glm::vec2{};

    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._separation_radius);
    for (auto const& closeMember : closeMembers)
        force += glm::normalize(getPosition() - closeMember.getPosition()) / glm::distance(getPosition(), closeMember.getPosition());

    return force * _forcesConfig._avoid_factor;
}

glm::vec2 SingleBoid::computeAlignmentForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._alignment_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averageVelocity = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averageVelocity += glm::normalize(closeMember.getVelocity());

    averageVelocity /= static_cast<float>(closeMembers.size());
    return (averageVelocity - getVelocity()) * _forcesConfig._matching_factor;
}

glm::vec2 SingleBoid::computeCohesionForce(std::vector<SingleBoid> const& boids) const
{
    std::vector<SingleBoid> const closeMembers = getNearbyBoids(boids, _forcesConfig._cohesion_radius);
    if (closeMembers.empty())
        return glm::vec2{};

    auto averagePosition = glm::vec2{};
    for (auto const& closeMember : closeMembers)
        averagePosition += glm::normalize(closeMember.getPosition());

    averagePosition /= static_cast<float>(closeMembers.size());
    return (averagePosition - getPosition()) * _forcesConfig._centering_factor;
}

std::vector<SingleBoid> SingleBoid::getNearbyBoids(std::vector<SingleBoid> const& boids, double radius) const
{
    return getNearbyBoidsFromPosition(getPosition(), boids, radius);
}

std::vector<SingleBoid> getNearbyBoidsFromPosition(glm::vec2 const& position, std::vector<SingleBoid> const& boids, double radius)
{
    std::vector<SingleBoid> nearbyBoids{};
    for (const auto& boid : boids)
    {
        if (boid.getPosition() == position)
            continue;

        if (glm::distance(position, boid.getPosition()) < radius)
            nearbyBoids.push_back(boid);
    }
    return nearbyBoids;
}
void SingleBoid::draw(p6::Context& ctx)
{
    std::visit([&](auto shape) {
        ctx.use_stroke = false;
        ctx.fill       = {1, 1, 1, 1};
        shape.draw(ctx, getTransformAttributes());
    }, _shape);
}
