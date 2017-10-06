#pragma once
#include <vector>
#include "Collidable.h"
#include "StaticCollider.h"
#include "DynamicCollider.h"
#include "Entity.h"

class CollisionHandler {
public:
    void checkCollisions();
    void registerCollider(Collidable*);
    void removeCollider(Collidable*&);
    void removeDynamicCollider(int);
    void removeStaticCollider(int);
    void clearDynamicColliders();
    void clearStaticColliders();
    void clearAll();

private:
    std::vector<StaticCollider*> mStaticColliders;
    std::vector<DynamicCollider*> mDynamicColliders;
};