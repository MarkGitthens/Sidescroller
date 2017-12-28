#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>

using std::string;
using std::vector;
class AABBCollider {
public:
    AABBCollider() {}
    AABBCollider(double, double, int, int);
	~AABBCollider();
    bool colliding(AABBCollider);

    vector<AABBCollider*> getColliders();

    void addCollider(AABBCollider*);

    void clearColliders();

    //Get the affected area of the colliding objects.
    double getInterArea(AABBCollider);

    Vector2D getProjectionVector(AABBCollider);

    Vector2D* getPos();

    bool isTrigger();

    void setTrigger(bool);

    virtual void handleCollisions() {};
    virtual void handleTrigger(string) {};
    virtual void updateAABB() {};
protected:
    vector<AABBCollider*> mColliders;
    Vector2D mPos;
    int mHalfWidth;
    int mHalfHeight;

    bool trigger = false;
};