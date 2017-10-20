#pragma once
#include "Vector2D.h"
#include <string>
#include <vector>
class AABBCollider {
public:
    AABBCollider() {}
    AABBCollider(double, double, int, int);

    bool colliding(AABBCollider);
    //Get the list of AABBColliders that are colliding with this collider.
    std::vector<AABBCollider*> getColliders();
    //Register a new currently colliding objects.
    void addCollider(AABBCollider*);
    //Clear the list of currently colliding objects. 
    void clearColliders();
    //Get the affected area of the colliding objects.
    double getInterArea(AABBCollider);
    //Returns a vector defining how far this object is colliding into the collider.
    Vector2D getProjectionVector(AABBCollider);
    //Get the position of this collider.
    Vector2D* getPos();
    //Returns true if this collider is a trigger
    bool isTrigger();
    //Set this collider to be a trigger or not
    void setTrigger(bool);

    virtual void handleCollision(std::string, AABBCollider) {};
    virtual void updateAABB() {};
protected:
    std::vector<AABBCollider*> mColliders;
    Vector2D pos;
    int mHalfWidth;
    int mHalfHeight;

    bool trigger = false;
};