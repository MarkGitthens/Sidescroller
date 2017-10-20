#include "Player.h"
#include <string>
#include <iostream>
#include "InputHandler.h"

int speed = 15;
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
        mVelocity.x = speed;
    } else if (InputHandler::getInstance().actionTriggered("move_left")) {
        mVelocity.x = -speed;
    } else {
        mVelocity.x = 0;
    }

    if (InputHandler::getInstance().actionTriggered("move_up")) {
        mVelocity.y = -speed;
    } else if (InputHandler::getInstance().actionTriggered("move_down")) {
        mVelocity.y = speed;
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
    while (!mColliders.empty()) {
        //Skip collision resolution if we are colliding with a trigger
        if (mColliders.at(0)->isTrigger()) {
            mColliders.erase(mColliders.begin());
            continue;   
        }
        //Determine the collider that provides the greatest impact on this entity
        double greatest = 0;
        int greatestIndex = 0;
        for (int i = 0; i < mColliders.size(); i++) {
            double temp = getInterArea(*mColliders.at(i));
            if (i == 0) {
                greatest = temp;
            } else if (temp > greatest) {
                greatestIndex = i;
                greatest = temp;
            }
        }
        pos = pos + getProjectionVector(*mColliders.at(greatestIndex));
        mColliders.erase(mColliders.begin() + greatestIndex);
    }
}

void Player::updateAABB() {
    pos.x = mRect.x + mHalfWidth;
    pos.y = mRect.y + mHalfHeight;
}   
