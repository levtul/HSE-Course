#include "circle.h"

Circle::Circle(const Point& center, const double& radius): Ellipse(center, center, radius * 2) {}

double Circle::radius() const {
    return a;
}