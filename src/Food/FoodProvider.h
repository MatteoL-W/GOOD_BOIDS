#pragma once

#include <p6/p6.h>
#include <iterator>
#include <list>

using Clock = std::chrono::high_resolution_clock;

struct FoodConfig {
    float _radius             = 0.05f;
    int   _providing_interval = 5;
    int   _drops              = 5;
    // Not unsigned for ImGui
};

class FoodProvider {
public:
    explicit FoodProvider(FoodConfig const& foodConfig, bool enableDrops = true);

    void enableRandomFood();
    void update(p6::Context&);
    void draw(p6::Context&) const;
    void erase(std::list<glm::vec2>::const_iterator it) { _foods.erase(it); };

    std::list<glm::vec2> const& getFood() const { return _foods; };
    float                       getFoodRadius() const { return _config._radius; };
    FoodConfig&                 getConfig() { return _config; };

private:
    void addFoodRandomly(p6::Context&);

private:
    std::optional<Clock::time_point> _randomFoodStartTime;
    std::list<glm::vec2>             _foods{};
    FoodConfig                       _config{};
};