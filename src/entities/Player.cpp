#include "Player.h"

const int speed = 8;
Player::Player(int x, int y, int width, int height) {
    mPos.x = x;
    mPos.y = y;
    mHalfWidth = width/2;
    mHalfHeight = height/2;

    Callback input = [this](Event* e) {
        this->handleInput(e);
    };

    SceneHandler::getInstance().getCurrentScene()->addListener(KeyboardEvent::KeyPress, input);
    SceneHandler::getInstance().getCurrentScene()->addListener(KeyboardEvent::KeyReleased, input);
}

void Player::update() {
    int gravity = 1;

    if(mVelocity.y < 30)
        mVelocity.y += gravity;

    mPos.x += mVelocity.x;
    mPos.y += mVelocity.y;
}

void Player::handleInput(Event* event) {

    KeyboardEvent* e = (KeyboardEvent*)event;
    if (event->getType() == KeyboardEvent::KeyPress) {
        if (e->keyID == SDLK_SPACE) {
            if (canJump) {
                canJump = false;
                mVelocity.y = -28;
            }
        }

        if (e->keyID == SDLK_RIGHT) {
            mVelocity.x += speed;
        }
        else if (e->keyID == SDLK_LEFT) {
            mVelocity.x += -speed;
        }
    }

    if (event->getType() == KeyboardEvent::KeyReleased) {
        if (e->keyID == SDLK_RIGHT) {
            mVelocity.x -= speed;
        }

        if (e->keyID == SDLK_LEFT) {
            mVelocity.x -= -speed;
        }
    }
}

void Player::fireBullet(int val) {
    Projectile* bullet = new Projectile(mPos.x, mPos.y, 10, 10, Vector2D(10, 0));
    bullet->createFromPath("resources/images/block.png", Game::getRenderer());
	bullet->setName("player_bullet"); 
	bullet->setTrigger(true);
	SceneHandler::getInstance().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
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

    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = 16;
    srcRect.h = 16;

    Renderer::getInstance().drawTexture(getTexture(), &srcRect, &destRect);
}

void Player::handleCollisions() {
    if (mColliders.empty()) {
        grounded = false;
    }
    else {
        canJump = true;
    }
    while (!mColliders.empty()) {
        
        //Determine the collider that provides the greatest impact on this entity
        double greatest = 0;
        int greatestIndex = 0;
        for (unsigned int i = 0; i < mColliders.size(); i++) {
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
        } else {
            grounded = false;
        }

        //hit bottom of object
        if(mVelocity.y < 0 && mPos.y- mHalfHeight >= mColliders.at(greatestIndex)->getPos()->y + mColliders.at(greatestIndex)->mHalfHeight) {
            mVelocity.y = 0;
        } 
        mColliders.erase(mColliders.begin() + greatestIndex);
    }
}

void Player::handleTrigger(std::string name) {
    if (name == "reset_box") {
        mPos.x = 64;
        mPos.y = 300;
    }
}