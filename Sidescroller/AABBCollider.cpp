#include "AABBCollider.h"
#include <iostream>
AABBCollider::AABBCollider(double x, double y, int w, int h) {
    pos.x = x;
    pos.y = y;

    mHalfWidth = w/2;
    mHalfHeight = h/2;
}

Vector2D* AABBCollider::getPos() {
    return &pos;
}
bool AABBCollider::colliding(AABBCollider col) {
    if (pos.x + mHalfWidth > col.pos.x - col.mHalfWidth && pos.x - mHalfWidth < col.pos.x + col.mHalfWidth
        && pos.y + mHalfHeight > col.pos.y - col.mHalfHeight && pos.y -mHalfHeight < col.pos.y + col.mHalfHeight) {
        return true;
    }
    return false;
}

void AABBCollider::addCollider(AABBCollider* collider) {
    mColliders.push_back(collider);
}

void AABBCollider::clearColliders() {
    mColliders.clear();
}

double AABBCollider::getInterArea(AABBCollider col) {
    int vecX = mHalfWidth + col.mHalfWidth - abs(pos.x - col.pos.x);
    int vecY = mHalfHeight + col.mHalfHeight - abs(pos.y - col.pos.y);

    return (Vector2D(vecX, vecY).magnitude());
}
Vector2D AABBCollider::getProjectionVector(AABBCollider col) {
    int vecX = mHalfWidth + col.mHalfWidth - abs(pos.x - col.pos.x);
    int vecY = mHalfHeight + col.mHalfHeight - abs(pos.y - col.pos.y);

    if (vecX <= vecY) {
        return Vector2D((pos.x < col.pos.x) ? -vecX : vecX , 0);
    } else {
        return Vector2D(0, (pos.y < col.pos.y) ? -vecY : vecY);
    }
}