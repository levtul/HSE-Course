#pragma once
#include "rectangle.h"
#include "circle.h"

struct Square : Rectangle {
    Square(const Point& first, const Point& second);

    Circle circumscribedCircle() const;
    Circle inscribedCircle() const;
};