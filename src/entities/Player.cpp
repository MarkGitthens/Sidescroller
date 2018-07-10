#include "Player.h"
#include <string>
#include <iostream>
#include "Projectile.h"
#include "../core/InputHandler.h"
#include "../core/SceneHandler.h"
const int speed = 8;
Player::Player(int x, int y, int width, int height) {
    mPos.x = x;
    mPos.y = y;
    mHalfWidth = width/2;
    mHalfHeight = height/2;
}
void Player::update() {
    handleInput();
    int gravity = 1;

    if(mVelocity.y < 30)
        mVelocity.y += gravity;

    mPos.x += mVelocity.x;
    mPos.y += mVelocity.y;
}

void Player::handleInput() {
    if (InputHandler::getInstance().actionHeld("move_right")) {
        mVelocity.x = speed;
    } else if (InputHandler::getInstance().actionHeld("move_left")) {
        mVelocity.x = -speed;
    } else {
        mVelocity.x = 0;
    }

    if (InputHandler::getInstance().actionTriggered("jump") && canJump) {
            mVelocity.y = -28;
    }
}

void Player::fireBullet(int val) {
    Projectile* bullet = new Projectile(mPos.x, mPos.y, 10, 10, Vector2D(10, 0));
	bullet->createFromPath("resources/images/block.png");
	bullet->setName("player_bullet"); 
	bullet->setTrigger(true);
	SceneHandler::getInstance().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
    mRect.x = x;
    mRect.y = y;

    mPos.x = x;
    mPos.y = y;
    mHalfHeight = 32;
    mHalfWidth = 32;
}

void Player::render(SDL_Rect* cameraRect) {
    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - cameraRect->x;
    destRect.y = mPos.y - mHalfHeight - cameraRect->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;
    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Player::handleCollisions() {
    if (mColliders.empty()) {
        canJump = false;
        grounded = false;
    }
    else {
        canJump = true;
    }
    while (!mColliders.empty()) {
        
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
        
        mPos = mPos + getProjectionVector(*mColliders.at(greatestIndex));
        
        //hit top of object
        if(mVelocity.y > 0 && mPos.y+mHalfHeight <= mColliders.at(greatestIndex)->getPos()->y - mColliders.at(greatestIndex)->mHalfHeight) {
            grounded = true;
            mVelocity.y = 0;
            std::cout << "grounded: " << grounded << std::endl;
        } else {
            grounded = false;
        }

        //hit bottom of object
        if(mVelocity.y < 0 && mPos.y- mHalfHeight >= mColliders.at(greatestIndex)->getPos()->y + mColliders.at(greatestIndex)->mHalfHeight) {
            mVelocity.y = 0;
        } 
        mColliders.erase(mColliders.begin() + greatestIndex);

        
        //TODO: Need to make this more intelligent.
    }
}

void Player::handleTrigger(std::string name) {
    if (name == "reset_box") {
        mPos.x = 64;
        mPos.y = 300;
    }
}

void Player::updateAABB() {
    mPos.x = mRect.x + mHalfWidth;
    mPos.y = mRect.y + mHalfHeight;
}   
