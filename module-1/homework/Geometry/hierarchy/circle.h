#pragma once
#include "ellipse.h"

struct Circle : Ellipse {
    Circle(const Point& center, const double& radius);
    
    double radius() const;
};