#pragma once
#include "core/Entity.h"
#include "core/Renderable.h"
#include "physics/AABBCollider.h"
#include "core/Game.h"

#include "Projectile.h"

class Patroller: public Entity, public Renderable, public AABBCollider {
public:
    Patroller(int x, int y, int w, int h);
    void handleXCollisions(const vector<AABBCollider*>&);
    void handleYCollisions(const vector<AABBCollider*>&);
    virtual void handleCollisions(AABBCollider*);
    virtual void update();
    virtual void render(SDL_Rect*);

private:
    Vector2D startPosition;
};