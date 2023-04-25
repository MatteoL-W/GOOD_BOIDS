#include "FoodProvider.h"
#include <chrono>
#include "Rendering/Shapes/ShapesRegister.h"

namespace Features {

FoodProvider::FoodProvider(FoodConfig const& foodConfig, bool enableDropsInstantly)
    : _config(foodConfig)
{
    if (enableDropsInstantly)
        enableDrop();
};

void FoodProvider::enableDrop()
{
    _randomFoodStartTime = Clock::now();
}

void FoodProvider::update(p6::Context& ctx)
{
    if (!_randomFoodStartTime.has_value())
        return;

    auto current_time = Clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - *_randomFoodStartTime).count();
    if (elapsed_time >= _config._providing_interval)
    {
        addFoodRandomly(ctx);
        _randomFoodStartTime = current_time;
    }
}

void FoodProvider::draw() const
{
    auto const& sphereShape = Rendering::Shapes::getSphereInstance(_config._radius);
    for (auto const& food : _foods)
    {
        std::visit(
            [&](auto const& sphereShape) {
                sphereShape.draw(utils::TransformAttributes{food}, glm::mat4{});
            },
            sphereShape
        );
    }
}

void FoodProvider::addFoodRandomly(p6::Context& ctx)
{
    for (int i = 0; i < _config._drops; i++)
        _foods.emplace_back(p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1), p6::random::number(-1, 1));
}

} // namespace Features
