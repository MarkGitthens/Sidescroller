#include "Camera.h"

Camera::Camera() {
    mCameraViewport = nullptr;
}

Camera::~Camera() {
    if (mCameraViewport)
        delete mCameraViewport;
    mCameraViewport = nullptr;
}

void Camera::update() {
    //Centers the camera to the center of the Parent and the screen.
    mCameraViewport->x = round(mParentPos->x) - mCameraViewport->w/2;
    mCameraViewport->y = round(mParentPos->y) - mCameraViewport->h/2;
    
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