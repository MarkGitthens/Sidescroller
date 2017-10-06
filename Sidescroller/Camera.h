#pragma once
#include <SDL.h>
#include "Vector2D.h"
#include "Entity.h"

class Camera : public Entity {
public:
    Camera();
    ~Camera();

    void update();
    
    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);
    void setCameraRect(SDL_Rect*);
    void setParentRect(SDL_Rect*);
    SDL_Rect* getCameraRect();
    SDL_Rect* getParentRect();
private:
    SDL_Rect* mParentRect;
    SDL_Rect* mCameraViewport;
};