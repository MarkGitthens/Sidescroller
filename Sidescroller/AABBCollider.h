#pragma once
#include "Vector2D.h"
#include <string>
class AABBCollider {
public:
    AABBCollider() {}
    AABBCollider(double, double, int, int);

    bool colliding(AABBCollider);
    Vector2D getProjectionVector(AABBCollider);
    Vector2D* getPos();
    virtual void handleCollision(std::string, AABBCollider) {};
    virtual void updateAABB() {};
protected:
    Vector2D pos;
    int mHalfWidth;
    int mHalfHeight;
};