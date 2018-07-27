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

    registerAnimation(Animation("resources/animations/playerWalk.xml"));
    registerAnimation(Animation("resources/animations/playerIdle.xml"));
    registerAnimation(Animation("resources/animations/playerJump.xml"));

    setAnimation("player_idle");
    SceneHandler::getInstance().getCurrentScene()->addListener(KeyboardEvent::KeyPress, input);
    SceneHandler::getInstance().getCurrentScene()->addListener(KeyboardEvent::KeyReleased, input);
}

void Player::update() {
    int gravity = 1;

    if(mVelocity.y < 30)
        mVelocity.y += gravity;

    mPos.x += mVelocity.x;
    mPos.y += mVelocity.y;

    if (mVelocity.x < 0)
            facingLeft = true;
    else if (mVelocity.x > 0)
            facingLeft = false;
    
    if(mVelocity.x != 0 && grounded) {
        setAnimation("player_walking");
    } else if (mVelocity.x == 0 && grounded) {
        setAnimation("player_idle");
    }

    if(!grounded) {
        setAnimation("player_jump");
    }
}

void Player::handleInput(Event* event) {

    KeyboardEvent* e = (KeyboardEvent*)event;
    if (event->getType() == KeyboardEvent::KeyPress) {
        if (e->keyID == SDLK_SPACE) {
            if (canJump) {
                canJump = false;
                mVelocity.y = -28;
                grounded = false;
            }
        }

        if(e->keyID == SDLK_e) {
            fireBullet();
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

void Player::render(SDL_Rect* cameraRect) {
    animations[currentAnimation].update();

    SDL_Rect destRect;
    destRect.x = mPos.x - mHalfWidth - cameraRect->x;
    destRect.y = mPos.y - mHalfHeight - cameraRect->y;
    destRect.w = mHalfWidth * 2;
    destRect.h = mHalfHeight * 2;

    if(!facingLeft) {
        Game::getRenderer().drawTexture(getTexture(), animations[currentAnimation].getCurrentFrame(), &destRect, 0, nullptr, SDL_FLIP_HORIZONTAL);
    } else {
        Game::getRenderer().drawTexture(getTexture(), animations[currentAnimation].getCurrentFrame(), &destRect, 0, nullptr);
    }
}

void Player::fireBullet() {
    Projectile* bullet = new Projectile(mPos.x, mPos.y, 10, 10, Vector2D(facingLeft ? -10 : 10, 0));
    bullet->createFromPath("resources/images/block.png", Game::getSDLRenderer());
	bullet->setName("player_bullet"); 
	bullet->setTrigger(true);
	Game::getSceneHandler().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
    mPos.x = x;
    mPos.y = y;
    mHalfHeight = 32;
    mHalfWidth = 32;
}

void Player::handleCollisions() {
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
            canJump = true;
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
