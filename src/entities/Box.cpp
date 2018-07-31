#include "Box.h"

void Box::update() {

}

void Box::handleInput() {

}

void Box::render(SDL_Rect* camera) {
    if (visible) {
        SDL_Rect destRect;
        destRect.x = mPos.x - mHalfWidth - camera->x;
        destRect.y = mPos.y - mHalfHeight - camera->y;
        destRect.w = mHalfWidth * 2;
        destRect.h = mHalfHeight * 2;
        Renderer::getInstance().drawTexture(getTexture(), &destRect);
    }
}

void Box::handleCollisions(AABBCollider*) {

}

void Box::updateAABB() {

}

bool Box::visibility() {
    return visible;
}
void Box::setVisible(bool visible) {
    this->visible = visible;
}