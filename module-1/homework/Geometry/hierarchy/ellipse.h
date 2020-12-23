#pragma once
#include "shape.h"
#include <vector>

struct Ellipse : public Shape {
public:
	Ellipse(const Point& focus1, const Point& focus2, const double& a2);

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
		
	std::pair<Point, Point> focuses() const;
	std::pair<Line, Line> directrices() const;
	double eccentricity() const;
	Point center() const;	
	
protected:
	Point focus1, focus2;
	double a, b, c;

};