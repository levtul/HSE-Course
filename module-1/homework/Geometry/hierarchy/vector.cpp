#include <cmath>
#include "point.h"
#include "vector.h"
#include "constants.h"
#include <iostream>
Vector::Vector(double _x, double _y): x(_x), y(_y) {}
Vector::Vector(const Point& point): x(point.x), y(point.y) {}
Vector::Vector(const Point& start, const Point& end) {
    x = end.x - start.x;
    y = end.y - start.y;
} 

Vector::Vector(const Vector& start, const Vector& end) {
    x = end.x - start.x;
    y = end.y - start.y;
} 

Vector Vector::operator+(const Vector& other) const {
    return Vector(x + other.x, y + other.y);
}
Vector Vector::operator-(const Vector& other) const {
    return Vector(x - other.x, y - other.y);
}
Vector Vector::operator-() const {
    return Vector(-x, -y);
}
Vector Vector::operator*(double num) const {
    return Vector(x * num, y * num);
}
Vector Vector::operator/(double num) const {
    return Vector(x / num, y / num);
}
double Vector::operator*(const Vector& other) const {
    return x * other.x + y * other.y;
}
double Vector::operator%(const Vector& other) const {
    return x * other.y - y * other.x;
}

bool Vector::operator==(const Vector& other) const {
    return std::fabs(x - other.x) <= EPS && std::fabs(y - other.y) <= EPS;
}
bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

double Vector::length() const {
    return std::sqrt(x*x + y*y);
}
double Vector::angle() const {
    return atan2(y, x);
}
double Vector::angle(const Vector& other) const {
    return atan2((*this % other), (*this * other));
}

Vector& Vector::rotate(double angle){
    double tmp_x = x * cos(angle) - y * sin(angle);
    y = x * sin(angle) + y * cos(angle);
    x = tmp_x;
    return *this;
}