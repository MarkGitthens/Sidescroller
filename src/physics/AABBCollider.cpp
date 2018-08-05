#include "AABBCollider.h"

AABBCollider::AABBCollider(int x, int y, int w, int h): mHalfWidth(w/2), mHalfHeight(h/2) {
    mPos.x = x;
    mPos.y = y;
}


void AABBCollider::setPos(double x, double y) {
    mPos.x = x;
    mPos.y = y;
}
Vector2D* AABBCollider::getPos() noexcept{
    return &mPos;
}

bool AABBCollider::colliding(const AABBCollider& col) noexcept {
    if (mPos.x + mHalfWidth > col.mPos.x - col.mHalfWidth && mPos.x - mHalfWidth < col.mPos.x + col.mHalfWidth
        && mPos.y + mHalfHeight > col.mPos.y - col.mHalfHeight && mPos.y -mHalfHeight < col.mPos.y + col.mHalfHeight) {
        return true;
    }
    return false;
}

AABBCollider::CollidedPosition AABBCollider::getCollidedPosition(const AABBCollider& col) {
    CollidedPosition pos = no_collision;
    //top
    if(mPos.y <= col.mPos.y - col.mHalfHeight) {
        //left
        if(mPos.x <= col.mPos.x) {
            pos = top_left;
        } else {
            pos = top_right;
        }
    } else {
        //left
        if(mPos.x <= col.mPos.x) {
            pos = bottom_left;
        } else {
            pos = bottom_right;
        }
    }

    return pos;
}

double AABBCollider::getInterArea(const AABBCollider& col) {
    if(!colliding(col))
        return 0;

    const double vecX = mHalfWidth + col.mHalfWidth - abs(mPos.x - col.mPos.x);
    const double vecY = mHalfHeight + col.mHalfHeight - abs(mPos.y - col.mPos.y);

    return (Vector2D(vecX, vecY).magnitude());
}

Vector2D AABBCollider::getProjectionVector(const AABBCollider& col) {
    if(!colliding(col))
        return Vector2D(0, 0);

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

