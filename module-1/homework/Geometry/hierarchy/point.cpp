#include "point.h"
#include "constants.h"
#include "vector.h"

Point::Point(const double& x, const double& y): x(x), y(y) {}

bool Point::operator==(const Point& other) const {
    return std::abs(x - other.x) <= EPS && std::abs(y - other.y) <= EPS;
}
bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}