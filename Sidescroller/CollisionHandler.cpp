#include "CollisionHandler.h"
#include <iostream>

void CollisionHandler::checkCollisions() {
    //iterate through the vectors to check collisions between dynamic entities and static entities
    for (DynamicCollider* d : mDynamicColliders) {
        for (StaticCollider* s : mStaticColliders) {
            if (d->collided(s)) {
                //TODO: Is there a way to do this without dynamic_casting?
                Entity* tempStatic = dynamic_cast<Entity*>(s);
                Entity* tempDynamic = dynamic_cast<Entity*>(d);

                if (tempStatic ) 
                    d->onCollision(tempStatic->getName());
                if (tempDynamic) 
                    s->onCollision(tempDynamic->getName());
            }
        }
    }

    //Check collisions between dynamic entities
    if (mDynamicColliders.size() > 1) {
        for (std::vector<DynamicCollider*>::iterator i = mDynamicColliders.begin(); i != mDynamicColliders.end()--; i++) {
            for (std::vector<DynamicCollider*>::iterator j = i++; j != mDynamicColliders.end(); ++j) {
                if ((*i)->collided(*j)) {
                    Entity* tempDyn1 = dynamic_cast<Entity*>(*i);
                    Entity* tempDyn2 = dynamic_cast<Entity*>(*j);

                    if (tempDyn1)
                        (*i)->onCollision(tempDyn2->getName());
                    if (tempDyn2)
                        (*j)->onCollision(tempDyn1->getName());
                }
            }
        }
    }
}

void CollisionHandler::registerCollider(Collidable* collider) {
    if (collider->getType() == Collidable::Type::dynamic_collider) {
        DynamicCollider* temp = dynamic_cast<DynamicCollider*>(collider);
        mDynamicColliders.emplace_back(temp);
    }
    else if (collider->getType() == Collidable::Type::static_collider) {
        StaticCollider* temp = dynamic_cast<StaticCollider*>(collider);
        mStaticColliders.emplace_back(temp);
    }
}

//void CollisionHandler::removeCollider(Collidable*& collider) {
//    switch (collider->getType()) {
//    case Collidable::Type::static_collider:
//        removeStaticCollider(collider->getID());
//        break;
//    case Collidable::Type::dynamic_collider:
//        removeDynamicCollider(collider->getID());
//        break;
//    default:
//        break;
//    }
//
//    if (collider)
//        delete collider;
//    collider = nullptr;
//}

void CollisionHandler::removeStaticCollider(int id) {
    mStaticColliders.erase(mStaticColliders.begin() + (id-1));
}

void CollisionHandler::removeDynamicCollider(int id) {
    mDynamicColliders.erase(mDynamicColliders.begin() + (id - 1));
}
void CollisionHandler::clearDynamicColliders() {
    mDynamicColliders.clear();
}

void CollisionHandler::clearStaticColliders() {
    mStaticColliders.clear();
}

void CollisionHandler::clearAll() {
    mDynamicColliders.clear();
    mStaticColliders.clear();
}