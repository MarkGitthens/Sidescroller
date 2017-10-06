#include "Collidable.h"

bool Collidable::collided(const Collidable* collider) {
    if (mBody.x < collider->mBody.x + collider->mBody.w && mBody.x + mBody.h > collider->mBody.x) {
        if (mBody.y < collider->mBody.y + collider->mBody.h && mBody.y + mBody.h > collider->mBody.y) {
            return true;
        }
    }
    return false;
}

SDL_Rect* Collidable::getRect() {
    return &mBody;
}

void Collidable::setDimensions(Vector2D dim) {
    mBody.w = dim.x;
    mBody.h = dim.y;
}

Vector2D Collidable::getDimensions() {
    Vector2D dimensions;
    
    dimensions.x = mBody.w;
    dimensions.y = mBody.h;

    return dimensions;
}

Vector2D Collidable::getPosition() {
    Vector2D pos;

    pos.x = mBody.x;
    pos.y = mBody.y;

    return pos;
}

