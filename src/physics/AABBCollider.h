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
    int mHalfHeight;
    AABBCollider() : mHalfWidth(0), mHalfHeight(0) {}
    AABBCollider(double, double, int, int);
	virtual ~AABBCollider();
    bool colliding(const AABBCollider&) noexcept;

    //returns where the collision occurs with respect to the caller
    CollidedPosition getCollidedPosition(const AABBCollider&);
    vector<AABBCollider*> getColliders();

    void addCollider(AABBCollider*);

    void clearColliders() noexcept;

    //Get the affected area of the colliding objects.
    double getInterArea(const AABBCollider&);

    Vector2D getProjectionVector(const AABBCollider&);

    Vector2D* getPos() noexcept;

    bool isTrigger();

    void setTrigger(bool);

    virtual void handleCollisions(AABBCollider*) {};
    virtual void handleTrigger(const string&) {};
    virtual void updateAABB() {};
protected:
    vector<AABBCollider*> mColliders;
    Vector2D mPos;
    int mHalfWidth;

    bool trigger = false;
};
