#pragma once
#include <cmath>
#include <SDL.h>
#include "../util/Vector2D.h"
#include "../core/Entity.h"

class Camera : public Vulture2D::Entity {
public:
    Camera();
    virtual ~Camera();

    void update();

    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);
    void setSceneWidth(int);
    void setSceneHeight(int);
    void setCameraRect(SDL_Rect*);
    void setParentPos(Vulture2D::Vector2D*);
    SDL_Rect* getCameraRect();
    Vulture2D::Vector2D* getParentPos();
private:
    int sceneWidth, sceneHeight;
    Vulture2D::Vector2D* mParentPos;
    SDL_Rect* mCameraViewport;
};
