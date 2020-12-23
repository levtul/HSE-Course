#include "triangle.h"

Triangle::Triangle(const Point& first, const Point& second, const Point& third): Polygon({first, second, third}) {}

Circle Triangle::circumscribedCircle() const {
    Point a = vtx[0], b = vtx[1], c = vtx[2];
    double z1 = a.x*a.x + a.y*a.y;
    double z2 = b.x*a.x + b.y*a.y;
    double z3 = c.x*a.x + c.y*a.y;
    double zx = (a.y-b.y)*z3 + (b.y-c.y)*z1 + (c.y-a.y)*z2;
    double zy = (a.x-b.x)*z3 + (b.x-c.x)*z1 + (c.x-a.x)*z2;
    double z = (a.x - b.x)*(c.y-a.y) - (a.y-b.y)*(c.x-a.x);
    double R = Vector(a,b).length() * Vector(a,c).length()*Vector(c,b).length()/fabs(Vector(a,b)%Vector(a,c)*2);
    return Circle(Point(-zx/(2*z), zy/(2*z)), R);
}
Circle Triangle::inscribedCircle() const {
    Vector v1 = Vector(vtx[0], vtx[1]);
    Vector v2 = Vector(vtx[0], vtx[2]);
    Vector v3 = Vector(vtx[1], vtx[2]);
    double r = fabs(v1 % v2) / (v1.length() + v2.length() + v3.length());
    double dist = r * 2 * v1.length() * v2.length() / (v1.length() * v2.length() - v1 * v2);
    Vector l = v1 / v1.length() + v2 / v2.length();
    Vector center = v1 + l / l.length() * dist;
    return Circle(Point(center.x, center.y), r);
}