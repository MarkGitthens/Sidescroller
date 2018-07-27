#include "Projectile.h"

void Projectile::update() {
    handleCollisions();
	mPos = mPos + mVelocity;
}

void Projectile::render(SDL_Rect* offset) {
	SDL_Rect destRect;
	destRect.x = mPos.x - mHalfWidth - offset->x;
	destRect.y = mPos.y - mHalfHeight - offset->y;
	destRect.w = mHalfWidth * 2;
	destRect.h = mHalfHeight * 2;
	Renderer::getInstance().drawTexture(image, &destRect);
}
void Projectile::handleCollisions() {
    for (auto c : mColliders) {
        if (dynamic_cast<Entity*>(c)->getName() == "Box") {
            SceneHandler::getInstance().getCurrentScene()->deleteEntity(getID());
        }
    }
}