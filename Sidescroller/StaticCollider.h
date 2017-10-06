#pragma once
#include "Collidable.h"
class StaticCollider : public Collidable {
public:
    virtual void onUpdate();
    virtual void resolveCollision(const Collidable * collider);
    virtual void onCollision(const char* name);
    virtual Type getType();
};