#include "Camera.h"


using namespace Vulture2D;

Camera::Camera() {
    mCameraViewport = nullptr;
}

Camera::~Camera() {
    if (mCameraViewport)
        delete mCameraViewport;
    mCameraViewport = nullptr;
}

void Camera::update() {
    
    if(mParentPos->x + mCameraViewport->w/2 <= loadedMap->getWidth()) {
        if(mParentPos->x - mCameraViewport->w/2 > 0) {
            mCameraViewport->x = round(mParentPos->x) - mCameraViewport->w/2;
        } else {
            mCameraViewport->x = 0;
        }    
    } else {
        mCameraViewport->x = loadedMap->getWidth() - mCameraViewport->w; 
    }
    
    if(mParentPos->y + mCameraViewport->h/2 <= loadedMap->getHeight()) {
        if(mParentPos->y - mCameraViewport->h/2 > 0) {
            mCameraViewport->y = round(mParentPos->y) - mCameraViewport->h/2;
        } else {
            mCameraViewport->y = 0;
        }
    } else {
        mCameraViewport->y = loadedMap->getHeight() - mCameraViewport->h;
    }
}

void Camera::setTiledMap(TiledMap* map) {
    loadedMap = map;
}

void Camera::setX(int x) {
    mCameraViewport->x = x;
}

void Camera::setY(int y) {
    mCameraViewport->y = y;
}

void Camera::setWidth(int width) {
    mCameraViewport->w = width;
}

void Camera::setHeight(int height) {
    mCameraViewport->h = height;
}

void Camera::setCameraRect(SDL_Rect* rect) {
    mCameraViewport = rect;
}
void Camera::setParentPos(Vector2D* parent) {
    mParentPos = parent;
}

SDL_Rect* Camera::getCameraRect() {
    return mCameraViewport;
}

Vector2D* Camera::getParentPos() {
    return mParentPos;
}
