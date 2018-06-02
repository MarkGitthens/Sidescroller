#pragma once
#include <string>
#include "../core/Entity.h"
#include "../physics/AABBCollider.h"

class ResetBox : public Vulture2D::Entity, public AABBCollider {
public:
    ResetBox() {};
    ResetBox(int x, int y, int w, int h) {
        mPos.x = x;
        mPos.y = y;
        mHalfWidth= w / 2;
        mHalfHeight = h / 2;
    }
    virtual void update() {};
    void handleInput() {};

    virtual void handleCollisions() {};
    virtual void handleTrigger(std::string) {};
    virtual void updateAABB() {};
};