#include "BreakableBox.h"
#include "Player.h"

void BreakableBox::handleCollisions(AABBCollider* c) {
    if(getCollidedPosition(*c) == top_left || getCollidedPosition(*c) == top_right) {
        Player* player = dynamic_cast<Player*>(c);
        if(player) {
            if(player->getName() == "player" && player->getVelocity().y < 0) {
                Game::getSceneHandler().getCurrentScene()->registerEntity(contains);
                Game::getSceneHandler().getCurrentScene()->deleteEntity(getID());
                Game::getSoundMixer().playSound(&sound);
            }
        }
    }
}

void BreakableBox::render(SDL_Rect* camera) {
    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - camera->x;
    destRect.y = mPos.y - mHalfHeight - camera->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;

    Game::getRenderer().drawTexture(image, &sheetPosition, &destRect);
}

void BreakableBox::setContains(Entity* entity) {
    contains = entity;
}
