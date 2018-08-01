#include "Patroller.h"

Patroller::Patroller(int x, int y, int w, int h) {
    this->x = x;
    this->y = y;

    startPosition.x = x;
    startPosition.y = y;

    mPos.x = x;
    mPos.y = y;

    velocity.x = 5;
    velocity.y = 10;

    mHalfHeight = h / 2;
    mHalfWidth = w / 2;
}


void Patroller::update() {
    if(fabs(mPos.x - startPosition.x) >= 400)
        velocity.x = -velocity.x;

    mPos.x = mPos.x + velocity.x;
    handleXCollisions(Game::getSceneHandler().getCurrentScene()->checkCollisions(this));

    mPos.y = mPos.y + velocity.y;
    handleYCollisions(Game::getSceneHandler().getCurrentScene()->checkCollisions(this));
}

void Patroller::handleXCollisions(const vector<AABBCollider*>& colliders) {
    if(colliders.empty())
        return;

    int greatestIndex = -1;

    for(int i = 0; i < colliders.size(); i++) {
        if(!colliders.at(i)->isTrigger()) {
            double greatest = 0;

            double temp = getInterArea(*colliders.at(i));
            if(temp > greatest) {
                greatestIndex = i;
                greatest = temp;
            }

            
        } 
        colliders.at(i)->handleCollisions(this);
        handleCollisions(colliders.at(i));
    }

    if(greatestIndex >= 0)
        mPos.x = mPos.x + getProjectionVector(*colliders.at(greatestIndex)).x;
}

void Patroller::handleYCollisions(const vector<AABBCollider*>& colliders) {
    int greatestIndex = -1;

    for(int i = 0; i < colliders.size(); i++) {
        if(!colliders.at(i)->isTrigger()) {
            double greatest = 0;

            double temp = getInterArea(*colliders.at(i));
            if(temp > greatest) {
                greatestIndex = i;
                greatest = temp;
            }
        }
        colliders.at(i)->handleCollisions(this);
        handleCollisions(colliders.at(i));
    }

    if(greatestIndex >= 0) {
        mPos.y = mPos.y + getProjectionVector(*colliders.at(greatestIndex)).y;
    }
}

void Patroller::handleCollisions(AABBCollider* collider) {
    Projectile* p = dynamic_cast<Projectile*>(collider);
    if(p)
        Game::getSceneHandler().getCurrentScene()->deleteEntity(getID());
}

void Patroller::render(SDL_Rect* camera) {
    if(visible) {
        SDL_Rect destRect;
        destRect.x = mPos.x - mHalfWidth - camera->x;
        destRect.y = mPos.y - mHalfHeight - camera->y;
        destRect.w = mHalfWidth * 2;
        destRect.h = mHalfHeight * 2;
        Renderer::getInstance().drawTexture(getTexture(), &destRect);
    }
}