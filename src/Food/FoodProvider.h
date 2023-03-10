#pragma once

#include <p6/p6.h>
#include <iterator>
#include <list>

class FoodProvider {
public:
    FoodProvider() = default;
    void draw(p6::Context&) const;
    void addFoodRandomly(p6::Context&);

    std::list<glm::vec2> const& getFood() const { return _foods; };
    float                       getFoodRadius() const { return _radius; };
    void                        erase(std::list<glm::vec2>::const_iterator it) { _foods.erase(it); };

private:
    std::list<glm::vec2> _foods{};
    float                _radius = 0.01f;
};