#pragma once
#include "point.h"
#include "vector.h"

struct Line {

    Line() = default;
    Line(const Point& first, const Point& second);

    bool operator==(const Line& other) const;
    bool operator!=(const Line& other) const;

    void update_coefficients();
    Line normalize() const;
    double distance(const Point& point) const;
    Vector proec(const Point& point) const;

    Point first, second;
    double a;
    double b;
    double c;
};