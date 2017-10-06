#pragma once
//Need to implement operator overloading
class Vector2D {
public:
    int x, y;
    Vector2D();
    Vector2D(const Vector2D&);
    Vector2D(int, int);
    ~Vector2D();
    Vector2D operator+(const Vector2D& right);
    Vector2D operator-(const Vector2D& right);
    Vector2D operator*(int scalar);
    Vector2D& operator=(const Vector2D& right);
};