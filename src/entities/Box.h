#pragma once
#include "../core/Entity.h"
#include "../core/Texture.h"
#include "../core/Renderable.h"
#include "../physics/AABBCollider.h"

class Box : public Vulture2D::Entity, public AABBCollider, public Vulture2D::Renderable {
public:
    Box(int x, int y, int w, int h) {
        this->x = x;
        this->y = y;

        mPos.x = x;
        mPos.y = y;

        mHalfHeight = h/2;
        mHalfWidth = w/2;
    }
    ~Box() {};
    void update() {};
    virtual void render(SDL_Rect*);
};