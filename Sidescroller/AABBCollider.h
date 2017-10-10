#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>
class AABBCollider {
public:
    AABBCollider() {}
    AABBCollider(double, double, int, int);

    bool colliding(AABBCollider);

    std::vector<AABBCollider*> getColliders();
    void addCollider(AABBCollider*);
    void clearColliders();
    double getInterArea(AABBCollider);
    Vector2D getProjectionVector(AABBCollider);
    Vector2D* getPos();
    
    virtual void handleCollision(std::string, AABBCollider) {};
    virtual void updateAABB() {};
protected:
    std::vector<AABBCollider*> mColliders;
    Vector2D pos;
    int mHalfWidth;
    int mHalfHeight;
};