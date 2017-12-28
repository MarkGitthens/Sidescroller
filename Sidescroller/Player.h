#pragma once
#include "Texture.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Renderable.h"
#include "AABBCollider.h"

class Player : public Entity, public AABBCollider, public Renderable {
public:
    Player() : mVelocity(0, 0){}
    Player(int, int, int, int);
    ~Player();
    virtual void update();
    void handleInput();

    virtual void handleCollisions();
    virtual void handleTrigger(std::string);
    virtual void updateAABB();

    virtual void render(SDL_Rect*);

    void setPosition(int x, int y);

	void fireBullet(int);
private:
    Vector2D mVelocity;
};