#include "ellipse.h"


Ellipse::Ellipse(const Point& focus1, const Point& focus2, const double& a2)
    : focus1(focus1), focus2(focus2), a(a2/2) {
        c = (Vector(focus1)-Vector(focus2)).length() / 2;
        b = sqrt(a*a - c*c);
}

double Ellipse::perimeter() const {
    return (PI * a * b + (a - b)) * 4 / (a + b);
}
double Ellipse::area() const {
    return a * b * PI;
}
bool Ellipse::operator==(const Shape& shape) const {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&shape);
    if (other == nullptr) {
        return false;
    }
    return fabs(a - other->a) < EPS &&
        (focus1 == other->focus1 && focus2 == other->focus2 || focus1 == other->focus2 && focus2 == other->focus1);
}
bool Ellipse::isCongruentTo(const Shape& shape) const {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&shape);
    if (other == nullptr) {
        return false;
    }
    return fabs(a - other->a) < EPS && fabs(c - other->c) < EPS;
}
bool Ellipse::isSimilarTo(const Shape& shape) const {
    const Ellipse* other = dynamic_cast<const Ellipse*>(&shape);
    if (other == nullptr) {
        return false;
    }
    return fabs(a - other->a * (c / other->c)) < EPS;
}
bool Ellipse::containsPoint(const Point& point) const {
    return (Vector(focus1, point) - Vector(focus2, point)).length() <= 2 * a + EPS;
}
Shape& Ellipse::rotate(const Point& center, const double& angle) {
    double r_angle = angle * PI / 180;
    Vector f1 = Vector(center) + Vector(center, focus1).rotate(r_angle);
    focus1 = Point(f1.x, f1.y);
    Vector f2 = Vector(center) + Vector(center, focus2).rotate(r_angle);
    focus2 = Point(f2.x, f2.y);
    return *this;
}
Shape& Ellipse::reflex(const Point& center) {
    Vector f1 = Vector(focus1) + Vector(focus1, center) * 2;
    focus1 = Point(f1.x, f1.y);
    Vector f2 = Vector(focus2) + Vector(focus2, center) * 2;
    focus2 = Point(f2.x, f2.y);
	return *this;
}
Shape& Ellipse::reflex(const Line& line) {
    Vector f1 = Vector(focus1) + Vector(focus1, line.proec(focus1)) * 2;
    focus1 = Point(f1.x, f1.y);
    Vector f2 = Vector(focus2) + Vector(focus2, line.proec(focus2)) * 2;
    focus2 = Point(f2.x, f2.y);
	return *this;
}
Shape& Ellipse::scale(const Point& center, const double& coef) {
    a *= coef;
    Vector f1 = Vector(center) + Vector(center, focus1) * coef;
    focus1 = Point(f1.x, f1.y);
    Vector f2 = Vector(center) + Vector(center, focus2) * coef;
    focus2 = Point(f2.x, f2.y);
    c = (Vector(focus1)-Vector(focus2)).length() / 2;
    b = sqrt(a*a - c*c);
    return *this;
}
std::pair<Point, Point> Ellipse::focuses() const {
    return {focus1, focus2};
}
std::pair<Line, Line> Ellipse::directrices() const {
    double common = (b * b / a) / (eccentricity() * (1 - eccentricity() * eccentricity()));
    return {Line(Point(0, -common), Point(1, -common)), Line(Point(0, common), Point(1, common))};
}
double Ellipse::eccentricity() const {
    return c / a;
}
Point Ellipse::center() const {
    Vector center = Vector(focus1) + Vector(focus1, focus2) / 2;
    return Point(center.x, center.y);
}