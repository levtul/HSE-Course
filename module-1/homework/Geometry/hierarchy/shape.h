#pragma once
#include "point.h"
#include "line.h"

struct Shape {

    virtual ~Shape() {}

    virtual double perimeter() const = 0;
    virtual double area() const = 0;

    virtual bool operator==(const Shape& shape) const = 0;
    virtual bool isCongruentTo(const Shape& shape) const = 0;
    virtual bool isSimilarTo(const Shape& shape) const = 0;
    
    virtual bool containsPoint(const Point& point) const = 0;

    virtual Shape& rotate(const Point& center, const double& angle) = 0;
    virtual Shape& reflex(const Point& center) = 0;
    virtual Shape& reflex(const Line& line) = 0;
    virtual Shape& scale(const Point& center, const double& coef) = 0;
};