#pragma once
#include <string>
#include "Projectile.h"
#include "../core/Game.h"
#include "../core/Entity.h"
#include "../core/AnimatedSprite.h"
#include "../physics/AABBCollider.h"
#include "../core/events/KeyboardEvent.h"

//TODO: Entities shouldn't inherit AABBCollider since a single entity have multiple colliders
class Player : public Vulture2D::Entity, public AABBCollider, public Vulture2D::AnimatedSprite {
public:
    Player(){};
    Player(int, int, int, int);
    virtual ~Player() {};
    virtual void update();
    void handleInput(Event*);

    void handleXCollisions(const vector<AABBCollider*>&);
    void handleYCollisions(const vector<AABBCollider*>&);
    virtual void handleCollisions(AABBCollider*);
    virtual void handleTrigger(const std::string&);

    virtual void render(SDL_Rect*);

    void setPosition(int x, int y);

	void fireBullet();

private:
    bool canJump = true;
    bool grounded = false;
    bool facingLeft = false;
};
