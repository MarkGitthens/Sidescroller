#include "Vector2D.h"
#include <iostream>
Vector2D::~Vector2D() {
    x = y = 0;
}

Vector2D::Vector2D(double x, double y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D& copy) {
    this->x = copy.x;
    this->y = copy.y;
}

//RHS normal of a vector
Vector2D Vector2D::normal() {
    return Vector2D(-y, x);
}

Vector2D Vector2D::normalize() {
    Vector2D temp(x, y);

    double vectorLength = sqrt(temp.x * temp.x + temp.y * temp.y);
    temp.x /= vectorLength;
    temp.y /= vectorLength;
    
    return temp;
}

double Vector2D::magnitude() {
    return sqrt(x*x + y*y);
}
double Vector2D::dot(Vector2D rhs) {
    return (x*rhs.x) + (y*rhs.y);
}

Vector2D Vector2D::project(Vector2D axis) {
    Vector2D projection;
    double dotP = dot(axis);

    projection.x = (dotP / (axis.x * axis.x + axis.y * axis.y)) * axis.x;
    projection.y = (dotP / (axis.x * axis.x + axis.y * axis.y)) * axis.y;

    return projection;
}
Vector2D Vector2D::operator+(const Vector2D& right) {
    this->x += right.x;
    this->y += right.y;
    return *this;
}

Vector2D Vector2D::operator-(const Vector2D& right) {
    this->x += right.x;
    this->y += right.y;
    return *this;
}

Vector2D Vector2D::operator*(int scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator=(const Vector2D& right) {
    this->x = right.x;
    this->y = right.y;
    return *this;
}