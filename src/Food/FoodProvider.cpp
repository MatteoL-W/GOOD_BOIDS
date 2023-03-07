#include "FoodProvider.h"
#include "Shapes/2D.h"

void FoodProvider::addFoodRandomly(p6::Context& ctx)
{
    _foods.emplace_back(p6::random::number(-ctx.aspect_ratio(), ctx.aspect_ratio()), p6::random::number(-1, 1));
}

void FoodProvider::draw(p6::Context& ctx)
{
    for (auto const& food : _foods)
    {
        ctx.fill = {1.f, .5f, .2f, 1.f};
        auto foodShape = Shapes::TwoDimensions::Circle{0.01f};
        foodShape.draw(ctx, Movement{food});
    }
}
