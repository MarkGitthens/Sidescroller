#pragma once
#include "../core/SceneHandler.h"
#include "../core/Entity.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"
#include "../core/Sound.h"
#include "../core/Game.h"

class Projectile : public Vulture2D::Entity, public Vulture2D::Renderable, public AABBCollider {
public:
	Projectile(double x, double y, int w, int h, Vector2D velocity) : AABBCollider(x,y,w,h), mVelocity(velocity) {
        sound = new Sound(Game::getAssetManager().getSound("bullet"));
        Game::getSoundMixer().playSound(sound);
    };
	void update();
	virtual void handleCollisions();
	void render(SDL_Rect*);

private:
	Vector2D mVelocity;
    Sound* sound;

};