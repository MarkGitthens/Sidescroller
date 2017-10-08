#pragma once
#include <math.h>
//Need to implement operator overloading
class Vector2D {
public:
    int x, y;
    Vector2D();
    Vector2D(const Vector2D&);
    Vector2D(int, int);
    ~Vector2D();

    int dot(Vector2D rhs);
    Vector2D normalize();
    Vector2D project(Vector2D line);
    Vector2D operator+(const Vector2D& right);
    Vector2D operator-(const Vector2D& right);
    Vector2D operator*(int scalar);
    Vector2D& operator=(const Vector2D& right);
};