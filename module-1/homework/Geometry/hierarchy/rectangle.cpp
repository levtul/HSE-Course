#include "rectangle.h"

Rectangle::Rectangle(const Point& first, const Point& second, const double& coef) {
    double diagonal = (Vector(first) - Vector(second)).length();
    double l_side = diagonal / sqrt(coef * coef + 1), s_side = l_side * coef;
    Vector v1 = Vector(first) + (Vector(first, second) * l_side / diagonal).rotate(atan(coef));
    Vector v2 = Vector(first) + (Vector(first, second) * s_side / diagonal).rotate(atan(coef) - PI / 2);
    vtx = {first, Point(v1.x, v1.y), second, Point(v2.x, v2.y)};
}

Point Rectangle::center() const {
    Vector center = (Vector(vtx[0]) + Vector(vtx[2])) / 2;
    return Point(center.x, center.y);
}

std::pair<Line, Line> Rectangle::diagonals() const {
    return {Line(vtx[0], vtx[2]), Line(vtx[1], vtx[3])};
}