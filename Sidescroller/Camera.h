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
    void setParentPos(Vector2D*);
    SDL_Rect* getCameraRect();
    Vector2D* getParentPos();
private:
    Vector2D* mParentPos;
    SDL_Rect* mCameraViewport;
};