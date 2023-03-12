#pragma once

#include "Shapes/2D.h"

enum SpeciesType {
    Prey,
    Predator,
};

class Species {
public:
    Species() = default;
    Species(ShapesType const& shape, SpeciesType const& type)
        : _shape(shape), _type(type) {}

    ShapesType getShape() { return _shape; };

private:
    ShapesType  _shape;
    SpeciesType _type;
};