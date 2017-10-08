#pragma once
#include <SDL.h>
#include "Vector2D.h"

//A collidable is a basic AABB object
class Collidable {
public:
    enum Type {
        dynamic_collider,
        static_collider
    };

    bool collided(const Collidable*);

    SDL_Rect* getRect();
    Vector2D getPosition();
    Vector2D getDimensions();

    void setDimensions(Vector2D);

    //Virtual functions to be implemented later.
    virtual void onUpdate() = 0;
    virtual void resolveCollision(const Collidable*) = 0;
    virtual void onCollision(const char*) = 0;

private:
    SDL_Rect mBody;
};