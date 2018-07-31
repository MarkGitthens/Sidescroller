#include "Camera.h"

using namespace Vulture2D;

Camera::Camera(): sceneWidth(0), sceneHeight(0), mCameraViewport(nullptr) {
    mParentPos = new Vector2D(0, 0);
}

Camera::~Camera() {
    delete mCameraViewport;
    mCameraViewport = nullptr;
}

void Camera::update() {
    if(mParentPos->x + mCameraViewport->w/2 <= sceneWidth) {
        if(mParentPos->x - mCameraViewport->w/2 > 0) {
            mCameraViewport->x = round(mParentPos->x) - mCameraViewport->w/2;
        } else {
            mCameraViewport->x = 0;
        }    
    } else {
        mCameraViewport->x = sceneWidth - mCameraViewport->w; 
    }
    
    if(mParentPos->y + mCameraViewport->h/2 <= sceneHeight) {
        if(mParentPos->y - mCameraViewport->h/2 > 0) {
            mCameraViewport->y = round(mParentPos->y) - mCameraViewport->h/2;
        } else {
            mCameraViewport->y = 0;
        }
    } else {
        mCameraViewport->y = sceneHeight - mCameraViewport->h;
    }
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
    delete mParentPos;

    mParentPos = parent;
}

void Camera::setSceneWidth(int width) {
    sceneWidth = width;
}

void Camera::setSceneHeight(int height) {
    sceneHeight = height;
}

SDL_Rect* Camera::getCameraRect() {
    return mCameraViewport;
}

Vector2D* Camera::getParentPos() {
    return mParentPos;
}
