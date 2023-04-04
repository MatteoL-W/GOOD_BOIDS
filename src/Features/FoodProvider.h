#pragma once

#include <iterator>
#include <list>
#include "p6/p6.h"

namespace Features {
using Clock = std::chrono::high_resolution_clock;

struct FoodConfig {
    /// The food providing interval in seconds.
    int _providing_interval = 5;

    /// The number of food dropping every interval
    int _drops = 5;

    /// The radius of the food
    float _radius = 0.05f;
};

class FoodProvider {
public:
    explicit FoodProvider(FoodConfig const& foodConfig, bool enableDropsInstantly = true);

    /// Enable the food dropping randomly in the map
    void enableDrop();
    void update(p6::Context&);
    void draw(p6::Context&) const;
    void erase(std::list<glm::vec3>::const_iterator it) { _foods.erase(it); };

    std::list<glm::vec3> const& getFood() const { return _foods; };
    float                       getFoodRadius() const { return _config._radius; };
    FoodConfig&                 getConfig() { return _config; };

private:
    // ToDo : Don't use ctx but screen values
    /// Add a new food randomly inside the map
    void addFoodRandomly(p6::Context&);

private:
    std::optional<Clock::time_point> _randomFoodStartTime;
    std::list<glm::vec3>             _foods{};
    FoodConfig                       _config{};
};

} // namespace Features