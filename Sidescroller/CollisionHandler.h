#pragma once
#include <vector>
#include "Collidable.h"
#include "Entity.h"

class CollisionHandler {
public:
    void checkCollisions();
    void registerCollider(Collidable*);
    void removeCollider(Collidable*&);

private:
};