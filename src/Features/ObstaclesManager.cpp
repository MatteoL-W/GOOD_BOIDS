#include "ObstaclesManager.h"
#include "Rendering/Shapes/ShapesRegister.h"

namespace Features {

void ObstaclesManager::draw(p6::Context& ctx)
{
    auto renderingDatas = utils::RenderingDatas{._renderType = utils::RenderType::Classic};
    for (auto const& obstacle : _obstacles)
    {
        auto const& sphereShape = Rendering::Shapes::getSphereInstance(obstacle._radius);
        if (!obstacle._visible)
            return;

        std::visit(
            [&](auto const& sphereShape) {
                sphereShape.draw(utils::TransformAttributes{obstacle._position}, renderingDatas);
            },
            sphereShape
        );
    }
}

void ObstaclesManager::addOne(glm::vec3 pos, float radius)
{
    _obstacles.push_back(SphereObstacle{glm::vec3{pos}, radius});
}

void ObstaclesManager::addRange(glm::vec3 start, glm::vec3 end, float radius)
{
    float        distance         = glm::distance(start, end);
    unsigned int numObstacles     = static_cast<unsigned int>(distance / (2 * radius + 0.01f));
    float        obstacleDistance = distance / static_cast<float>(numObstacles);
    glm::vec3    direction        = glm::normalize(end - start);

    for (unsigned int i = 0; i < numObstacles; i++)
    {
        glm::vec3 position = start + direction * static_cast<float>(i) * obstacleDistance;
        addOne(position, radius);
    }
}

// void ObstaclesManager::add2DMapDelimiters(float screenHalfWidth, float screenHalfHeight)
//{
//     static float constexpr obstacleRadius = .1f;
//     addRange({-screenHalfWidth, screenHalfHeight + obstacleRadius}, {screenHalfWidth, screenHalfHeight + obstacleRadius}, obstacleRadius);
//     addRange({-screenHalfWidth, -screenHalfHeight - obstacleRadius}, {screenHalfWidth, -screenHalfHeight - obstacleRadius}, obstacleRadius);
//     addRange({-screenHalfWidth - obstacleRadius, -screenHalfHeight}, {-screenHalfWidth - obstacleRadius, screenHalfHeight}, obstacleRadius);
//     addRange({screenHalfWidth + obstacleRadius, -screenHalfHeight}, {screenHalfWidth + obstacleRadius, screenHalfHeight}, obstacleRadius);
// }

/*void ObstaclesManager::addRectangle(glm::vec3 topLeft, glm::vec3 bottomRight, float radius)
{
    auto topRight = glm::vec3{bottomRight.x, topLeft.y, bottomRight.z};

    auto currentLeft = topLeft;
    auto currentRight = topRight;

    if (topLeft.y != bottomRight.y) {
        while (currentLeft.y > bottomRight.y && currentRight.y > bottomRight.y) {
            addRange(currentLeft, currentRight, radius);
            currentLeft.y -= radius * 2;
            currentRight.y -= radius * 2;
        }
    } else {
        // ToDo
    }

}

void ObstaclesManager::add3DMapDelimiters()
{
    static float space = 5.f;

    // Depth
    addRectangle({-5.f, 5.f, -5.f}, {5.f, -5.f, -5.f}, .2f);
    addRectangle({-5.f, 5.f, 5.f}, {5.f, -5.f, 5.f}, .2f);

    // X
    addRectangle({5.f, 5.f, -5.f}, {5.f, -5.f, 5.f}, .2f);
    addRectangle({-5.f, 5.f, -5.f}, {-5.f, -5.f, 5.f}, .2f);

    // Y
    addRectangle({-5.f, 5.f, 5.f}, {5.f, 5.f, -5.f}, .2f);
}*/

} // namespace Features