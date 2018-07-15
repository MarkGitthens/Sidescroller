#pragma once
#include <string>
#include "Projectile.h"
#include "../core/Game.h"
#include "../core/Entity.h"
#include "../core/AnimatedSprite.h"
#include "../physics/AABBCollider.h"
#include "../core/KeyboardEvent.h"

//TODO: Entities shouldn't inherit AABBCollider since a single entity have multiple colliders
class Player : public Vulture2D::Entity, public AABBCollider, public Vulture2D::AnimatedSprite {
public:
    Player() : mVelocity(0, 0) {};
    Player(int, int, int, int);
    virtual void update();
    void handleInput(Event*);

    virtual void handleCollisions();
    virtual void handleTrigger(std::string);

    virtual void render(SDL_Rect*);

    void setPosition(int x, int y);

	void fireBullet(int);
private:
    bool canJump = true;
    bool grounded = false;
    Vector2D mVelocity;
};
