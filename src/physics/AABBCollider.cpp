#include "AABBCollider.h"

AABBCollider::AABBCollider(double x, double y, int w, int h) {
    mPos.x = x;
    mPos.y = y;

    mHalfWidth = w/2;
    mHalfHeight = h/2;
}

AABBCollider::~AABBCollider() {
	mColliders.clear();
    //std::cout << "destroying aabb" << std::endl;
}
Vector2D* AABBCollider::getPos() noexcept{
    return &mPos;
}
bool AABBCollider::colliding(AABBCollider col) noexcept {
    if (mPos.x + mHalfWidth > col.mPos.x - col.mHalfWidth && mPos.x - mHalfWidth < col.mPos.x + col.mHalfWidth
        && mPos.y + mHalfHeight > col.mPos.y - col.mHalfHeight && mPos.y -mHalfHeight < col.mPos.y + col.mHalfHeight) {
        return true;
    }
    return false;
}

void AABBCollider::addCollider(AABBCollider* collider) {
    mColliders.push_back(collider);
}

void AABBCollider::clearColliders() noexcept {
    mColliders.clear();
}

double AABBCollider::getInterArea(AABBCollider col) {
    const double vecX = mHalfWidth + col.mHalfWidth - abs(mPos.x - col.mPos.x);
    const double vecY = mHalfHeight + col.mHalfHeight - abs(mPos.y - col.mPos.y);

    return (Vector2D(vecX, vecY).magnitude());
}
Vector2D AABBCollider::getProjectionVector(AABBCollider col) {
    const double vecX = mHalfWidth + col.mHalfWidth - abs(mPos.x - col.mPos.x);
    const double vecY = mHalfHeight + col.mHalfHeight - abs(mPos.y - col.mPos.y);

    if (vecX <= vecY) {
        return Vector2D((mPos.x < col.mPos.x) ? -vecX : vecX , 0);
    } else {
        return Vector2D(0, (mPos.y < col.mPos.y) ? -vecY : vecY);
    }
}

bool AABBCollider::isTrigger() {
    return trigger;
}

void AABBCollider::setTrigger(bool val) {
    trigger = val;
}

