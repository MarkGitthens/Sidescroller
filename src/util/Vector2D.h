#pragma once
#include <math.h>
//Need to implement operator overloading
namespace Vulture2D {
    class Vector2D {
    public:
        double x, y;
        Vector2D() : x(0), y(0) {};
        Vector2D(const Vector2D&);
        Vector2D(double, double);
        ~Vector2D();

        double dot(const Vector2D& rhs);
        Vector2D normal();
        Vector2D normalize();
        double magnitude();
        Vector2D project(const Vector2D& line);
        Vector2D operator+(const Vector2D& right);
        Vector2D operator-(const Vector2D& right);
        Vector2D operator*(double scalar);
        Vector2D& operator=(const Vector2D& right);
        bool operator==(const Vector2D& right);
        bool operator!=(const Vector2D& right);

    };
}