#include "Coin.h"

Coin::Coin(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;

    mPos.x = x;
    mPos.y = y;

    mHalfHeight = h / 2;
    mHalfWidth = w / 2;
}

void Coin::handleCollisions(AABBCollider* collider) {
    Entity* player = dynamic_cast<Entity*>(collider);
    if(player) {
        Game::getSceneHandler().getCurrentScene()->deleteEntity(getID());
    }
}

void Coin::render(SDL_Rect* camera) {
    if(visible) {
        SDL_Rect destRect;
        destRect.x = mPos.x - mHalfWidth - camera->x;
        destRect.y = mPos.y - mHalfHeight - camera->y;
        destRect.w = mHalfWidth * 2;
        destRect.h = mHalfHeight * 2;
        Renderer::getInstance().drawTexture(getTexture(), &destRect);
    }
}