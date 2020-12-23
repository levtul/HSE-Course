#pragma once
#include "point.h"
struct Vector {
    double x, y;

    Vector() = default;
    Vector(double _x, double _y);
    Vector(const Point& point);
    Vector(const Point& start, const Point& end); 
    Vector(const Vector& start, const Vector& end); 
    
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator-() const;
    Vector operator*(double num) const;
    Vector operator/(double num) const;
    double operator*(const Vector& other) const;
    double operator%(const Vector& other) const;

    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const;
    
    double length() const;
    double angle() const;
    double angle(const Vector& other) const;

    Vector& rotate(double angle);
};