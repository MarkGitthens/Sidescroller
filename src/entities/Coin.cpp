#include "Coin.h"

Coin::Coin() : sound(Game::getAssetManager().getSound("coin")) {}

void Coin::handleCollisions(AABBCollider* collider) {
    Entity* player = dynamic_cast<Entity*>(collider);
    if(player)
        Game::getSoundMixer().playSound(&sound);
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