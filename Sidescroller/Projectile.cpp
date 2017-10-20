#include "Projectile.h"

void Projectile::update() {
	mPos = mPos + mVelocity;
}

void Projectile::render(SDL_Rect* offset) {
	SDL_Rect destRect;
	destRect.x = mPos.x - mHalfWidth - offset->x;
	destRect.y = mPos.y - mHalfHeight - offset->y;
	destRect.w = mHalfWidth * 2;
	destRect.h = mHalfHeight * 2;
	Renderer::getInstance().drawTexture(mImage, &destRect);
}
void Projectile::handleCollision() {

}