#include "line.h"
#include "vector.h"
#include "constants.h"

Line::Line(const Point& first, const Point& second) {
    this->first = Point(first);
    this->second = Point(second);
    update_coefficients();
}

void Line::update_coefficients() {
    a = first.y - second.y;
    b = second.x - first.x;
    c = Vector(first) % Vector(second);
}

bool Line::operator==(const Line& other) const {
    Line l1 = normalize(), l2 = other.normalize();
    return (l1.a - l2.a < EPS) && (l1.b - l2.b < EPS) && (l1.c - l2.c < EPS);
}

bool Line::operator!=(const Line& other) const {
    return !(*this == other);
}

Line Line::normalize() const {
    Line l = *this;
    double den = sqrt(a * a + b * b);
    l.a /= den;
    l.b /= den;
    l.c /= den;
    if (a < 0) {
        l.a = -l.a;
        l.b = -l.b;
        l.c = -l.c;
    }
    return l;
}

double Line::distance(const Point& point) const{
    return (a * point.x + b * point.y + c) / std::sqrt(a * a + b * b);
}

Vector Line::proec(const Point& point) const {
    Vector normal = Vector(a, b);
	return Vector(point) - normal / normal.length() * distance(point);
}
