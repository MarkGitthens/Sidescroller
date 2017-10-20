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

    bool colliding(AABBCollider);
    //Get the list of AABBColliders that are colliding with this collider.
    vector<AABBCollider*> getColliders();
    //Register a new currently colliding objects.
    void addCollider(AABBCollider*);
    //Clear the list of currently colliding objects. 
    void clearColliders();
    //Get the affected area of the colliding objects.
    double getInterArea(AABBCollider);
    //Returns a vector defining how far this object is colliding into the collider.
    Vector2D getProjectionVector(AABBCollider);
    //Get the mPosition of this collider.
    Vector2D* getPos();
    //Returns true if this collider is a trigger
    bool isTrigger();
    //Set this collider to be a trigger or not
    void setTrigger(bool);

    virtual void handleCollision(string, AABBCollider) {};
    virtual void updateAABB() {};
protected:
    vector<AABBCollider*> mColliders;
    Vector2D mPos;
    int mHalfWidth;
    int mHalfHeight;

    bool trigger = false;
};