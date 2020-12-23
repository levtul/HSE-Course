#pragma once
#include "constants.h"
#include <cmath>

struct Point {
    double x;
    double y;

    Point() = default;
    Point(const double& x, const double& y);

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};