#pragma once
#include "Entity.h"
#include "Renderable.h"
#include "AABBCollider.h"

class Projectile : public Vulture2D::Entity, public Vulture2D::Renderable, public AABBCollider {
public:
	Projectile(double x, double y, int w, int h, Vector2D velocity) : AABBCollider(x,y,w,h), mVelocity(velocity) {};
    virtual ~Projectile();
	void update();
	virtual void handleCollisions();
	void render(SDL_Rect*);

private:
	Vector2D mVelocity;

};