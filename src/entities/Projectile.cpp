#include "Projectile.h"

void Projectile::update() {
	mPos = mPos + velocity;

    if(fabs(startPosition.x - mPos.x) >= 600) {
        destroy();
    }

    vector<AABBCollider*> colliders = Game::getSceneHandler().getCurrentScene()->checkCollisions(this);

    for(auto c : colliders) {
        c->handleCollisions(this);
        if(dynamic_cast<Entity*>(c)->getName() != "player") {
            destroy();
        }
    }
}

void Projectile::destroy() {
    SceneHandler::getInstance().getCurrentScene()->deleteEntity(getID());
}

void Projectile::render(SDL_Rect* offset) {
	SDL_Rect destRect;
	destRect.x = mPos.x - mHalfWidth - offset->x;
	destRect.y = mPos.y - mHalfHeight - offset->y;
	destRect.w = mHalfWidth * 2;
	destRect.h = mHalfHeight * 2;
	Renderer::getInstance().drawTexture(image, &destRect);
}

void Projectile::handleCollisions(AABBCollider*) {

}