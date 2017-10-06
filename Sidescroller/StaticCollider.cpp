#include "StaticCollider.h"

void StaticCollider::onUpdate() {

}

void StaticCollider::resolveCollision(const Collidable* collider) {

}

void StaticCollider::onCollision(const char* name) {

}

Collidable::Type StaticCollider::getType() {
    return Type::static_collider;
}