#pragma once
#include "../core/Entity.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"
#include "../core/Sound.h"
#include "../core/Game.h"

class Coin: public Entity, public Renderable, public AABBCollider {
public:
    Coin(int x, int y, int w, int h);
    virtual void handleCollisions(AABBCollider*);
    virtual void update() {};
    virtual void render(SDL_Rect*);


private:
    //Sound sound;
};