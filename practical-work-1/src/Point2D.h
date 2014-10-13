#pragma once

#include <iostream>

class Point2D {
	double x, y;
public:
	Point2D();
	Point2D(double x, double y);
	Point2D(const Point2D& point);
	virtual ~Point2D();

	double getX() const;
	void setX(double x);
	double getY() const;
	void setY(double y);

	Point2D& operator=(const Point2D &point) {
		if (this == &point)
			return *this;

		x = point.x;
		y = point.y;

		return *this;
	}

	friend Point2D operator+(Point2D start, Point2D vec) {
		double x, y;

		x = start.x + vec.x;
		y = start.y + vec.y;

		return Point2D(x, y);
	}

	friend Point2D operator-(Point2D end, Point2D start) {
		double x, y;

		x = end.x - start.x;
		y = end.y - start.y;

		return Point2D(x, y);
	}

	friend Point2D operator*(double n, Point2D vec) {
		double x, y;

		x = n * vec.x;
		y = n * vec.y;

		return Point2D(x, y);
	}

	Point2D& operator/=(double n) {
		this->x /= n;
		this->y /= n;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& out, const Point2D& point) {
		out << "(" << point.x << ", " << point.y << ")";
		return out;
	}
};

