#pragma once

#include "p6/p6.h"
#include <list>

class FoodProvider {
public:
    FoodProvider() = default;
    void draw(p6::Context&);
    void addFoodRandomly(p6::Context&);

private:
    std::list<glm::vec2> _foods;
};