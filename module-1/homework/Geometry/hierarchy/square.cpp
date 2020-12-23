#include "square.h"

Square::Square(const Point& first, const Point& second): Rectangle(first, second, 1) {}

Circle Square::circumscribedCircle() const {
    return Circle(center(), Vector(vtx[0], vtx[2]).length() / 2);
}
Circle Square::inscribedCircle() const {
    return Circle(center(), Vector(vtx[0], vtx[1]).length() / 2);
}