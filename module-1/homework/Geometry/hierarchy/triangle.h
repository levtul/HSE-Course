#pragma once
#include "polygon.h"
#include "circle.h"

struct Triangle: Polygon {
    Triangle(const Point& first, const Point& second, const Point& third);

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
    
};