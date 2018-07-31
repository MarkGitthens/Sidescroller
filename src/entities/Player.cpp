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

    Sound sound(Game::getAssetManager().getSound("bgMusic"), true);
    Game::getSoundMixer().playSound(&sound);
}

void Player::update() {
    int gravity = 1;

    if(velocity.y < 30)
        velocity.y += gravity;

    mPos.x += velocity.x;
    handleXCollisions(Game::getSceneHandler().getCurrentScene()->checkCollision(this));

    mPos.y += velocity.y;
    handleYCollisions(Game::getSceneHandler().getCurrentScene()->checkCollision(this));

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

void Player::handleXCollisions(const vector<AABBCollider*>& colliders) {
    if(colliders.empty())
        return;
    size_t greatestIndex = 0;

    for(int i = 0; i < colliders.size(); i++) {
        double greatest = 0;

        double temp = getInterArea(*colliders.at(i));
        if(temp > greatest) {
            greatestIndex = i;
            greatest = temp;
        }

        colliders.at(i)->handleCollisions(this);
    }

    mPos.x = mPos.x + getProjectionVector(*colliders.at(greatestIndex)).x;
}

void Player::handleYCollisions(const vector<AABBCollider*>& colliders) {
    size_t greatestIndex = 0;
    if(colliders.empty()) {
        grounded = false;
        return;
    }

    for(int i = 0; i < colliders.size(); i++) {
        double greatest = 0;

        double temp = getInterArea(*colliders.at(i));
        if(temp > greatest) {
            greatestIndex = i;
            greatest = temp;
        }

        colliders.at(i)->handleCollisions(this);
    }

    AABBCollider* greatestCollider = colliders.at(greatestIndex);
    int collidedPosition = getCollidedPosition(*greatestCollider);
    if(velocity.y > 0 && (collidedPosition == top_left || collidedPosition == top_right)) {
        grounded = true;
        velocity.y = 0;
        canJump = true;
    } else {
        grounded = false;
    }

    //hit bottom of object
    if(velocity.y < 0 && (getCollidedPosition(*greatestCollider) == bottom_left || getCollidedPosition(*greatestCollider) == bottom_right)) {
        velocity.y = 0;
    }

   
    mPos.y = mPos.y + getProjectionVector(*colliders.at(greatestIndex)).y;
}

void Player::handleCollisions(AABBCollider*) {
}

void Player::handleTrigger(const std::string& name) {
    if (name == "reset_box") {
        mPos.x = 64;
        mPos.y = 300;
    }
}
