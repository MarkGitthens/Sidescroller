#pragma once
#include "../core/Texture.h"
#include "../core/Entity.h"
#include "../core/InputHandler.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"

//TODO: Entities shouldn't inherit AABBCollider since a single entity have multiple colliders
class Player : public Vulture2D::Entity, public AABBCollider, public Vulture2D::Renderable {
public:
    Player() : mVelocity(0, 0) {};
    Player(int, int, int, int);
    virtual void update();
    void handleInput();

    virtual void handleCollisions();
    virtual void handleTrigger(std::string);
    virtual void updateAABB();

    virtual void render(SDL_Rect*);

    void setPosition(int x, int y);

	void fireBullet(int);
private:
    bool canJump = true;
    bool grounded = false;
    Vector2D mVelocity;
};
