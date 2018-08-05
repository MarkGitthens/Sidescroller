#include "Collision_test.h"
#include <iostream>

void Collision_test::init() {

}

bool Collision_test::testColliding() {
    bool passed = true;
    AABBCollider a(0, 0, 40, 40);

    AABBCollider b(-1000, 0, 40, 40);

    std::cout << a.colliding(b) << std::endl;
    if(a.colliding(b))
        passed = false;

    b.setPos(25, 0);
    std::cout << a.colliding(b) << std::endl;
    if(!a.colliding(b))
        passed = false;

    b.setPos(40, 0);
    std::cout << a.colliding(b) << std::endl;
    if(a.colliding(b))
        passed = false;

    return passed;
}
bool Collision_test::testInterArea() {
    bool passed = true;
    AABBCollider a(0, 0, 40, 40);

    AABBCollider b(-1000, 0, 40, 40);

    std::cout << a.getInterArea(b) << std::endl;
    if(a.getInterArea(b) != 0)
        passed = false;

    Vector2D test(20, 40);

    b.setPos(-20, 0);
    std::cout << a.getInterArea(b) << ", " << test.magnitude() << std::endl;
    if(a.getInterArea(b) != test.magnitude())
        passed = false;

    b.setPos(0, 0);

    test.x = 40;
    test.y = 40;

    std::cout << a.getInterArea(b) << ", " << test.magnitude() << std::endl;
    if(a.getInterArea(b) != test.magnitude())
        passed = false;

    return passed;
}
bool Collision_test::testProjectionVector() {
    bool passed = true;

    AABBCollider a(0, 0, 40, 40);
    AABBCollider b(-1000, 0, 40, 40);

    Vector2D projection = a.getProjectionVector(b);
    
    std::cout << projection.x << ", " << projection.y << std::endl;
    if(projection != Vector2D(0,0))
        passed = false;

    b.setPos(-20, 0);
    projection = a.getProjectionVector(b);

    std::cout << projection.x << ", " << projection.y << std::endl;
    if(projection != Vector2D(20, 0))
        passed = false;

    b.setPos(0, 0);
    projection = a.getProjectionVector(b);

    std::cout << projection.x << ", " << projection.y << std::endl;
    if(projection != Vector2D(40, 0))
        passed = false;

    b.setPos(0, 20);
    projection = a.getProjectionVector(b);

    std::cout << projection.x << ", " << projection.y << std::endl;
    if(projection != Vector2D(0, -20))
        passed = false;
    
    return passed;
}

bool Collision_test::run() {
    std::cout << "Running Collision tests." << std::endl;
    return testColliding() && testInterArea() && testProjectionVector();
}