#pragma once
#include "Collidable.h"

class DynamicCollider : public Collidable {
public:
    virtual void onUpdate();
    virtual void resolveCollision(const Collidable*);
    virtual void onCollision(const char* name);
    virtual Type getType();
};