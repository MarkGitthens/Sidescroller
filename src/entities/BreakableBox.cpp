#include "BreakableBox.h"

BreakableBox::BreakableBox() {

    loadSheetPosition();
}

BreakableBox::BreakableBox(int x, int y, int w, int h) {
    mPos.x = x;
    mPos.y = y;

    mHalfHeight = h / 2;
    mHalfWidth = w / 2;

    loadSheetPosition();
}

BreakableBox::BreakableBox(SDL_Rect dimensions) {
    mPos.x = dimensions.x;
    mPos.y = dimensions.y;
    mHalfHeight = dimensions.w / 2;
    mHalfHeight = dimensions.h / 2;

    loadSheetPosition();
}

void BreakableBox::handleCollisions() {

}

void BreakableBox::render(SDL_Rect* camera) {
    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - camera->x;
    destRect.y = mPos.y - mHalfHeight - camera->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;

    Game::getRenderer().drawTexture(image, &sheetPosition, &destRect);
}