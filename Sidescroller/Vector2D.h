#pragma once
#include <math.h>
//Need to implement operator overloading
class Vector2D {
public:
    double x, y;
    Vector2D() : x(0), y(0) {};
    Vector2D(const Vector2D&);
    Vector2D(double, double);
    ~Vector2D();

    double dot(Vector2D rhs);
    Vector2D normal();
    Vector2D normalize();
    Vector2D project(Vector2D line);
    Vector2D operator+(const Vector2D& right);
    Vector2D operator-(const Vector2D& right);
    Vector2D operator*(int scalar);
    Vector2D& operator=(const Vector2D& right);
};