#pragma once
#include "Entity.h"
#include "Texture.h"
#include "Renderable.h"
#include "AABBCollider.h"

class Box : public Entity, public AABBCollider, public Renderable {
public:
    Box(): mTexture(nullptr) {};
    Box(int x, int y, int w, int h) {
        pos.x = x;
        pos.y = y;

        mHalfHeight = h/2;
        mHalfWidth = w/2;
    }
    Box(Texture* texture) : mTexture(texture) {};
    ~Box();
    void update();
    void handleInput();
    virtual void render(SDL_Rect*);

    virtual void handleCollision(std::string, AABBCollider);
    virtual void updateAABB();
private:
    Texture* mTexture;
};