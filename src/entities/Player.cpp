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

    Sound* sound = new Sound(Game::getAssetManager().getSound("bgMusic"), true);
    Game::getSoundMixer().playSound(sound);
}

void Player::update() {
    int gravity = 1;

    if(velocity.y < 30)
        velocity.y += gravity;

    mPos.x += velocity.x;
    mPos.y += velocity.y;

    if (velocity.x < 0)
            facingLeft = true;
    else if (velocity.x > 0)
            facingLeft = false;
    
    if(grounded) {
        if(fabs(velocity.x) >= 0.1) {
            setAnimation("player_walking");
        } else {
            setAnimation("player_idle");
        }
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
                velocity.y = -30;
                grounded = false;
            }
        }

        if(e->keyID == SDLK_e) {
            fireBullet();
        }
        if (e->keyID == SDLK_RIGHT) {
            velocity.x += speed;
        }
        else if (e->keyID == SDLK_LEFT) {
            velocity.x += -speed;
        }
    }

    if (event->getType() == KeyboardEvent::KeyReleased) {
        if (e->keyID == SDLK_RIGHT) {
            velocity.x -= speed;
        }

        if (e->keyID == SDLK_LEFT) {
            velocity.x -= -speed;
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
    Projectile* bullet = new Projectile(mPos.x, mPos.y, 10, 10, Vector2D(facingLeft ? -15 : 15, 0));
    bullet->setSprite(AssetManager::getInstance().getTexture("block"));
    bullet->setName("player_bullet"); 
	bullet->setTrigger(true);
	Game::getSceneHandler().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
    mPos.x = x;
    mPos.y = y;
}

//TODO: I really need to find a better way to resolve collisions. As it is now my method doesn't work as intended.
void Player::handleCollisions() {
    if(mColliders.empty())
        grounded = false;

    while (!mColliders.empty()) {
        
        //Determine the collider that provides the greatest impact on this entity
        double greatest = 0;
        size_t greatestIndex = 0;
        for (size_t i = 0; i < mColliders.size(); i++) {
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
        AABBCollider* greatestCollider = mColliders.at(greatestIndex);
        if(velocity.y > 0 && (getCollidedPosition(*greatestCollider) == top_left || getCollidedPosition(*greatestCollider) == top_right)) {
            grounded = true;
            velocity.y = 0;
            canJump = true;
        } else {
            grounded = false;
        }

        //hit bottom of object
        if(velocity.y < 0 && mPos.y- mHalfHeight >= greatestCollider->getPos()->y + greatestCollider->mHalfHeight) {
            velocity.y = 0;
        }

        mColliders.erase(mColliders.begin() + greatestIndex);
    }
}

void Player::handleTrigger(const std::string& name) {
    if (name == "reset_box") {
        mPos.x = 64;
        mPos.y = 300;
    }
}
