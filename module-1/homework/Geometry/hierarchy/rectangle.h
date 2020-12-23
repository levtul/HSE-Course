#pragma once
#include "polygon.h"

struct Rectangle : Polygon {
    Rectangle(const Point& first, const Point& second, const double& coef);

    Point center() const;
    std::pair<Line, Line> diagonals() const;
};