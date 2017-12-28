#pragma once
#include "Entity.h"
#include "Texture.h"
#include "Renderable.h"
#include "AABBCollider.h"

class Box : public Entity, public AABBCollider, public Renderable {
public:
    Box(): mTexture(nullptr) {};
    Box(int x, int y, int w, int h) {
        mPos.x = x;
        mPos.y = y;

        mHalfHeight = h/2;
        mHalfWidth = w/2;
    }
    Box(Texture* texture) : mTexture(texture) {};
    virtual ~Box();
    void update();
    void handleInput();
    virtual void render(SDL_Rect*);

    virtual void handleCollisions();
    virtual void updateAABB();
private:
    Texture* mTexture;
};