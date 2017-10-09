#include "Player.h"
#include <string>
#include <iostream>
#include "InputHandler.h"

Player::Player(int x, int y, int width, int height) {
    pos.x = x;
    pos.y = y;
    mHalfWidth = width/2;
    mHalfHeight = height/2;
}
void Player::update() {
    handleInput();

    pos.x += mVelocity.x;
    pos.y += mVelocity.y;
}

void Player::handleInput() {
    if (InputHandler::getInstance().actionTriggered("move_right")) {
        mVelocity.x = 3;
    } else if (InputHandler::getInstance().actionTriggered("move_left")) {
        mVelocity.x = -3;
    } else {
        mVelocity.x = 0;
    }

    if (InputHandler::getInstance().actionTriggered("move_up")) {
        mVelocity.y = -3;
    } else if (InputHandler::getInstance().actionTriggered("move_down")) {
        mVelocity.y = 3;
    } else {
        mVelocity.y = 0;
    }
}

void Player::setPosition(int x, int y) {
    mRect.x = x;
    mRect.y = y;

    pos.x = x;
    pos.y = y;
    mHalfHeight = 32;
    mHalfWidth = 32;
}

void Player::render(SDL_Rect* cameraRect) {
    SDL_Rect destRect;
    destRect.x = pos.x - mHalfWidth - cameraRect->x;
    destRect.y = pos.y - mHalfHeight - cameraRect->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;
    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Player::handleCollision(std::string name, AABBCollider col) {
    pos = pos + getProjectionVector(col);
}

void Player::updateAABB() {
    pos.x = mRect.x + mHalfWidth;
    pos.y = mRect.y + mHalfHeight;
}   
