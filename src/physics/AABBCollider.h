#pragma once
#include "../util/Vector2D.h"
#include <string>
#include <vector>

using std::string;
using std::vector;

using namespace Vulture2D;

class AABBCollider {
public:
    int mHalfHeight;
    AABBCollider() : mHalfWidth(0), mHalfHeight(0) {}
    AABBCollider(double, double, int, int);
	virtual ~AABBCollider();
    bool colliding(AABBCollider) noexcept;

    vector<AABBCollider*> getColliders();

    void addCollider(AABBCollider*);

    void clearColliders() noexcept;

    //Get the affected area of the colliding objects.
    double getInterArea(AABBCollider);

    Vector2D getProjectionVector(AABBCollider);

    Vector2D* getPos() noexcept;

    bool isTrigger();

    void setTrigger(bool);

    virtual void handleCollisions() {};
    virtual void handleTrigger(string) {};
    virtual void updateAABB() {};
protected:
    vector<AABBCollider*> mColliders;
    Vector2D mPos;
    int mHalfWidth;

    bool trigger = false;
};
