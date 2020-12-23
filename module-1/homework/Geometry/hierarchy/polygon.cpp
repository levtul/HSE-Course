#include "constants.h"
#include "polygon.h"
#include "point.h"
#include "vector.h"
#include "line.h"

#include <iostream>

Polygon::Polygon(std::vector<Point> vtx): vtx(vtx) {}

double Polygon::perimeter() const {
    double result = 0;
    for (size_t i = 0; i < vtx.size(); i++) {
        result += Vector(vtx[i], vtx[(i + 1) % vtx.size()]).length();
    }
    return result;
}
double Polygon::area() const {
    double result = 0;
    for (size_t i = 1; i + 1 < vtx.size(); i++) {
        result += Vector(vtx[0], vtx[i]) % Vector(vtx[0], vtx[i + 1]);
    }
    return std::fabs(result / 2);
}

bool Polygon::operator==(const Shape& shape) const {
    const auto* other = dynamic_cast<const Polygon*>(&shape);
    if (other->vtx.size() != vtx.size()) {
        return 0;
    }
    for (int s = 0; s < vtx.size(); s++) {
        bool equal = 1;
        for (size_t i = 0; i < vtx.size(); i++) {
            if (vtx[i] != other->vtx[(i + s) % vtx.size()]) {
                equal = 0;
                break;
            }
        }
        if (equal) {
            return 1;
        }
    }
    return 0;
}
bool Polygon::isCongruentTo(const Shape& shape) const {
    const auto* other = dynamic_cast<const Polygon*>(&shape);
    if (other == nullptr) {
        return 0;
    }
    if (other->vtx.size() != vtx.size()) {
        return 0;
    }
    std::vector<Vector> vec(vtx.size()), other_vec(vtx.size());
    for (size_t i = 0; i < vtx.size(); i++) {
        vec[i] = Vector(vtx[i], vtx[(i + 1) % vtx.size()]);
        other_vec[i] = Vector(other->vtx[i], other->vtx[(i + 1) % vtx.size()]);
    }
    for (size_t s = 0; s < vtx.size(); s++) {
        bool congruent = 1;
        for (size_t i = 0; i < vtx.size(); i++) {
            if (vec[i] != other_vec[(i + s) % vtx.size()]) {
                congruent = 0;
                break;
            }
        }
        if (congruent) {
            return 1;
        }
    }
    return 0;
}
bool Polygon::isSimilarTo(const Shape& shape) const {
    const auto* other = dynamic_cast<const Polygon*>(&shape);
    if (other == nullptr) {
        return 0;
    }
    if (other->vtx.size() != vtx.size()) {
        return 0;
    }
    std::vector<Vector> vec(vtx.size()), other_vec(vtx.size());
    for (size_t i = 0; i < vtx.size(); i++) {
        vec[i] = Vector(vtx[i], vtx[(i + 1) % vtx.size()]);
        other_vec[i] = Vector(other->vtx[i], other->vtx[(i + 1) % vtx.size()]);
    }
    for (size_t s = 0; s < vtx.size(); s++) {
        bool similar = 1;
        double relation = 0;
        for (size_t i = 0; i < vtx.size(); i++) {
            double len = vec[i].length();
            double other_len = other_vec[(i + s) % vtx.size()].length();

            if (relation == 0) {
                relation = len / other_len;
                continue;
            }
            if (len - other_len * relation > EPS) {
                similar = 0;
                break;
            }
        }
        if (similar) {
            return 1;
        }
    }
    return 0;
}

bool Polygon::containsPoint(const Point& point) const {
    double angle_sum = 0;
    Vector vec(point);
    for (size_t i = 0; i < vtx.size(); i++) {
        Vector cur(vtx[i]), next(vtx[(i + 1) % vtx.size()]);
        angle_sum += (cur - vec).angle(next-vec);
        if ((vec - cur).length() + (vec-next).length() - (cur-next).length() < EPS) {
            return 1;
        }
    }
    return fabs(angle_sum - 2*PI) < EPS;
}

Shape& Polygon::rotate(const Point& center, const double& angle) {
    double r_angle = angle * PI / 180;
    for (size_t i = 0; i < vtx.size(); i++) {
		Vector rotated = Vector(center) + Vector(center, vtx[i]).rotate(r_angle);
        vtx[i] = Point(rotated.x, rotated.y);
	}
	return *this;
}
Shape& Polygon::reflex(const Point& center) {
    for (size_t i = 0; i < vtx.size(); i++) {
        Vector reflected = Vector(vtx[i]) + Vector(vtx[i], center) * 2;
		vtx[i] = Point(reflected.x, reflected.y);
	}
	return *this;
}
Shape& Polygon::reflex(const Line& line) {
    for (size_t i = 0; i < vtx.size(); i++) {
        Vector reflected = Vector(vtx[i]) + Vector(vtx[i], line.proec(vtx[i])) * 2;
		vtx[i] = Point(reflected.x, reflected.y);
	}
	return *this;
}
Shape& Polygon::scale(const Point& center, const double& coef) {
    for (size_t i = 0; i < vtx.size(); i++) {
        Vector scaled = Vector(center) + Vector(center, vtx[i]) * coef;
		vtx[i] = Point(scaled.x, scaled.y);
	}
	return *this;
}

int Polygon::verticesCount() const {
    return vtx.size();
}
std::vector<Point> Polygon::getVertices() const {
    return vtx;
}
bool Polygon::isConvex() const {
    for (int i = 0; i < vtx.size(); i++) {
		Vector a = Vector(vtx[i]), b = Vector(vtx[(i + 1) % vtx.size()]);
        Vector c = Vector(vtx[(i + 2) % vtx.size()]);
		if ((b - a) % (c - b) < 0) {
			return 0;
		}
	}
	return 1;
}
