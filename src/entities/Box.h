#pragma once
#include "../core/Entity.h"
#include "../core/Texture.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"

class Box : public Vulture2D::Entity, public AABBCollider, public Vulture2D::Renderable {
public:
    Box(): mTexture(nullptr) {};
    Box(int x, int y, int w, int h) : mTexture(nullptr) {
        mPos.x = x;
        mPos.y = y;

        mHalfHeight = h/2;
        mHalfWidth = w/2;
    }
    Box(Texture* texture) : mTexture(texture) {};
    
    void update();
    void handleInput();
    virtual void render(SDL_Rect*);
    virtual void handleCollisions(AABBCollider*);
    virtual void updateAABB();
    bool visibility();
    void setVisible(bool);

private:
    Texture* mTexture;
    bool visible = true;
};