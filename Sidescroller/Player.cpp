#include "Player.h"
#include <string>
#include <iostream>
#include "InputHandler.h"

void Player::update() {
    SDL_Rect* physicsBody = getRect();
    //Do basic physics
    //DynamicCollider::onUpdate();
    handleInput();

    physicsBody->x += mVelocity.x;
    physicsBody->y += mVelocity.y;
}

void Player::handleInput() {
    if (InputHandler::getInstance().actionTriggered("move_right")) {
        mVelocity.x = 5;
    } else if (InputHandler::getInstance().actionTriggered("move_left")) {
        mVelocity.x = -5;
    } else {
        mVelocity.x = 0;
    }

    if (InputHandler::getInstance().actionTriggered("move_up")) {
        mVelocity.y = -5;
    } else if (InputHandler::getInstance().actionTriggered("move_down")) {
        mVelocity.y = 5;
    } else {
        mVelocity.y = 0;
    }
}

void Player::render(SDL_Rect* cameraRect) {
    SDL_Rect destRect = *(getRect());
    destRect.x -= cameraRect->x;
    destRect.y -= cameraRect->y;
    Renderer::getInstance().drawTexture(getTexture(), &destRect);
}

void Player::onCollision(const char* name) {
    std::string temp(name);
    if (temp == "floor") {
    }
    std::cout << "Colliding with " << name << std::endl;
}