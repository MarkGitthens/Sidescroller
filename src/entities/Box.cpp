#include "Box.h"

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