#include "Vector2D_test.h"
#include <iostream>

void Vector2D_test::init() {}

bool Vector2D_test::testDot() {
    bool passed = true;
    
    a.x = 0;
    a.y = 0;

    b.x = 0;
    b.y = 1;

    std::cout << a.dot(b) << std::endl;
    if(a.dot(b) != 0)
        passed = false;
    
    a.x = 1;
    a.y = 0;

    b.x = 1;
    b.y = 1;

    std::cout << a.dot(b) << std::endl;
    if(a.dot(b) != 1)
        passed = false;


    a.x = 0;
    a.y = 5;

    b.x = 1;
    b.y = 1;

    std::cout << a.dot(b) << std::endl;
    if(a.dot(b) != 5)
        passed = false;

    return passed;
}

bool Vector2D_test::testSimpleArithmetic() {
    bool passed = true;

    a.x = 1;
    a.y = 1;

    b.x = 1;
    b.y = 1;

    a = a + b;
    std::cout << a.x << ", " << a.y << std::endl;
    if(a.x != 2 || a.y != 2)
        passed = false;

    a.x = 1;
    a.y = 1;

    b.x = 1;
    b.y = 1;

    a = a - b;
    std::cout << a.x << ", " << a.y << std::endl;
    if(a.x != 0 || a.y != 0)
        passed = false;

    a.x = 1;
    a.y = 1;

    a = a * 5;
    std::cout << a.x << ", " << a.y << std::endl;
    if(a.x != 5 || a.y != 5)
        passed = false;

    a.x = 1;
    a.y = 1;

    a = a * -5;
    std::cout << a.x << ", " << a.y << std::endl;
    if(a.x != -5 || a.y != -5)
        passed = false;

    a.x = 1;
    a.y = 1;

    a = a * .5;
    std::cout << a.x << ", " << a.y << std::endl;
    if(a.x != .5 || a.y != .5)
        passed = false;

    return passed;
}

bool Vector2D_test::testNormal() {
    bool passed = true;

    a.x = 5;
    a.y = 1;

    b.x = 1;
    b.y = -5;

    

    std::cout << a.x << ", " << a.y << ", " << b.x << ", " << b.y << std::endl;

    a = a.normal();
    if(a != b)
        passed = false;

    return passed;
}

bool Vector2D_test::testMagnitude() {
    bool passed = true;

    a.x = 5;
    a.y = 0;

    std::cout << a.magnitude() << std::endl;
    if(a.magnitude() != 5)
        passed = false;

    return passed;
}

bool Vector2D_test::testNormalize() {
    bool passed = true;

    a.x = 5;
    a.y = 0;

    b.x = 1;
    b.y = 0;

    a = a.normalize();

    std::cout << a.x << ", " << a.y << std::endl;
    if(a != b)
        passed = false;

    return passed;
}

bool Vector2D_test::run() {
    std::cout << "Running Vector2D tests." << std::endl;
    return testDot() && testSimpleArithmetic() && testNormal() && testMagnitude() && testNormalize();
}