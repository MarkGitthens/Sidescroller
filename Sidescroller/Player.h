#pragma once
#include "Texture.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Renderable.h"

class Player : public Entity, public Renderable {
public:
    Player() : mVelocity(0, 0){}
    ~Player();
    virtual void update();
    void handleInput();
    virtual void onCollision(const char*);

    virtual void render(SDL_Rect*);

    void setPosition(int x, int y);
private:
    Vector2D mVelocity;
};