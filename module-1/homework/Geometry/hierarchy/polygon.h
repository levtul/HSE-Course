#pragma once
#include "shape.h"

#include <vector>

struct Polygon: Shape {
public:
    Polygon() = default;
    Polygon(std::vector<Point> verticles);

    int verticesCount() const;
    std::vector<Point> getVertices() const;
    bool isConvex() const;

    double perimeter() const override;
    double area() const override;

    bool operator==(const Shape& shape) const override;
    bool isCongruentTo(const Shape& shape) const override;
    bool isSimilarTo(const Shape& shape) const override;

    bool containsPoint(const Point& point) const override;
    
    Shape& rotate(const Point& center, const double& angle) override;
    Shape& reflex(const Point& center) override;
    Shape& reflex(const Line& line) override;
    Shape& scale(const Point& center, const double& coef) override;

protected:
    std::vector<Point> vtx;
};