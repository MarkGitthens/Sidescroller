#include "Vector2D.h"

Vector2D::Vector2D() {
    x = y = 0;
}

Vector2D::~Vector2D() {
    x = y = 0;
}

Vector2D::Vector2D(int x, int y) {
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const Vector2D& copy) {
    this->x = copy.x;
    this->y = copy.y;
}

Vector2D Vector2D::normalize() {
    Vector2D temp(x, y);

    double vectorLength = sqrt(temp.x * temp.x + temp.y * temp.y);
    temp.x /= vectorLength;
    temp.y /= vectorLength;
    
    return temp;
}

int Vector2D::dot(Vector2D rhs) {
    return x*rhs.x + y*rhs.y;
}

Vector2D Vector2D::project(Vector2D line) {
    Vector2D projection;
    projection.x = (dot(line) / (line.x * line.x + line.y*line.y)) * line.x;
    projection.x = (dot(line) / (line.x * line.x + line.y*line.y)) * line.y;

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