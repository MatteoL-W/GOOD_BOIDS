#include "FoodProvider.h"
#include <chrono>
#include "Shapes/2D.h"

FoodProvider::FoodProvider(FoodConfig const& foodConfig, bool enableDrops)
    : _config(foodConfig)
{
    if (enableDrops)
        enableRandomFood();
};

void FoodProvider::enableRandomFood()
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

void FoodProvider::draw(p6::Context& ctx) const
{
    for (auto const& food : _foods)
    {
        ctx.fill       = {1.f, .5f, .2f, 1.f};
        auto foodShape = Shapes::TwoDimensions::Circle{_config._radius};
        foodShape.draw(ctx, utils::TransformAttributes{food});
    }
}

void FoodProvider::addFoodRandomly(p6::Context& ctx)
{
    for (int i = 0; i < _config._drops; i++)
        _foods.emplace_back(p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1));
}
