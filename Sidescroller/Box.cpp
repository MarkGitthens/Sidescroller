#include "Box.h"

Box::~Box() {
    if (mTexture) {
        delete mTexture;
    }
    mTexture = nullptr;
}
void Box::update() {

}

void Box::handleInput() {

}

void Box::render(SDL_Rect* camera) {
    SDL_Rect destRect;
    destRect.x = mPos.x -mHalfWidth - camera->x;
    destRect.y = mPos.y - mHalfHeight - camera->y;
    destRect.w = mHalfWidth*2;
    destRect.h = mHalfHeight*2;
    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Box::handleCollisions() {

}

void Box::updateAABB() {

}