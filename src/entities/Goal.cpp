#include "Goal.h"

Goal::Goal(int x, int y, int w, int h, std::string sceneName) {
    this->x = x;
    this->y = y;
    
    mPos.x = x;
    mPos.y = y;
    mHalfWidth = w/2;
    mHalfHeight = h/2;

    nextScene = sceneName;
}

void Goal::render(SDL_Rect* camera) {
    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - camera->x;
    destRect.y = mPos.y - mHalfHeight - camera->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;

    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Goal::handleCollisions(AABBCollider* c) {
    if(getCollidedPosition(*c) == top_left || getCollidedPosition(*c) == top_right) {
        Player* player = dynamic_cast<Player*>(c);
        if(player) {
            SceneHandler::getInstance().changeScene(nextScene);
        }
    }
}