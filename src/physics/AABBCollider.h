#pragma once
#include "../util/Vector2D.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

using namespace Vulture2D;

class AABBCollider {
public:
    enum CollidedPosition {
        no_collision,
        top_right,
        top_left,
        bottom_right,
        bottom_left,
    };

public:
    AABBCollider(int x = 0, int y = 0, int w = 1, int h = 1);
    bool colliding(const AABBCollider&) noexcept;

    //returns where the collision occurs with respect to the caller
    CollidedPosition getCollidedPosition(const AABBCollider&);

    //Get the affected area of the colliding objects.
    double getInterArea(const AABBCollider&);

    Vector2D getProjectionVector(const AABBCollider&);

    void setPos(double, double);
    Vector2D* getPos() noexcept;

    bool isTrigger();

    void setTrigger(bool);

    virtual void handleCollisions(AABBCollider*) {};
    virtual void handleTrigger(const string&) {};
    virtual void updateAABB() {};
protected:
    Vector2D mPos;
    int mHalfWidth;
    int mHalfHeight;

    bool trigger = false;
};
