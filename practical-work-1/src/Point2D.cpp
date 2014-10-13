#include "Point2D.h"

Point2D::Point2D() {
	x = y = 0;
}

Point2D::Point2D(double x, double y) {
	this->x = x;
	this->y = y;
}

Point2D::Point2D(const Point2D& point) {
	this->x = point.x;
	this->y = point.y;
}

Point2D::~Point2D() {
}

double Point2D::getX() const {
	return x;
}

void Point2D::setX(double x) {
	this->x = x;
}

double Point2D::getY() const {
	return y;
}

void Point2D::setY(double y) {
	this->y = y;
}

