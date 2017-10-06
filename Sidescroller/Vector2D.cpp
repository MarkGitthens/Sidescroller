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