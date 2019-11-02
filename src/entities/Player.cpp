#include "Player.h"

#include "PlayerIdle.h"
#include "PlayerState.h"

Player::Player(int x, int y, int width, int height) {
  mPos.x = x;
  mPos.y = y;
  mHalfWidth = width / 2;
  mHalfHeight = height / 2;

  registerAnimation(Animation("resources/animations/playerWalk.xml"));
  registerAnimation(Animation("resources/animations/playerIdle.xml"));
  registerAnimation(Animation("resources/animations/playerJump.xml"));

  state = new PlayerIdle(this);
}

Player::~Player() {
  if (state) delete state;
}

void Player::update() {
  PlayerState* nextState = state->update(this);
  if (nextState) {
    state->exit(this);
    delete state;
    state = nextState;
  }
}

void Player::start() {
  velocity.x = velocity.y = 0;

  Callback input = [this](Event* e) { this->handleInput(e); };

  Scene* currentScene = SceneHandler::getInstance().getCurrentScene();
  setAnimation("player_idle");
  registeredCallbacks.push_back(
      currentScene->addListener(KeyboardEvent::KeyPress, input));
  registeredCallbacks.push_back(
      currentScene->addListener(KeyboardEvent::KeyReleased, input));

  //   Sound sound(Game::getAssetManager().getSound("bgMusic"), true);
  // Game::getSoundMixer().playSound(&sound);
}

void Player::stop() {
  for (auto i : registeredCallbacks) {
    SceneHandler::getInstance().getCurrentScene()->removeListener(i);
  }
}

void Player::handleInput(Event* event) {
  PlayerState* nextState = state->handleInput(this, event);
  if (nextState) {
    state->exit(this);
    delete state;
    state = nextState;
  }
}

void Player::render(SDL_Rect* cameraRect) {
  animations[currentAnimation].update();

  SDL_Rect destRect;
  destRect.x = mPos.x - mHalfWidth - cameraRect->x;
  destRect.y = mPos.y - mHalfHeight - cameraRect->y;
  destRect.w = mHalfWidth * 2;
  destRect.h = mHalfHeight * 2;

  if (!facingLeft) {
    Game::getRenderer().drawTexture(
        getTexture(), animations[currentAnimation].getCurrentFrame(), &destRect,
        0, nullptr, SDL_FLIP_HORIZONTAL);
  } else {
    Game::getRenderer().drawTexture(
        getTexture(), animations[currentAnimation].getCurrentFrame(), &destRect,
        0, nullptr);
  }
}

void Player::fireBullet() {
  Projectile* bullet =
      new Projectile(mPos.x, mPos.y, 8, 8, Vector2D(facingLeft ? -15 : 15, 0));
  bullet->setSprite(AssetManager::getInstance().getTexture("block"));
  bullet->setName("player_bullet");
  Game::getSceneHandler().getCurrentScene()->registerEntity(bullet);
}

void Player::setPosition(int x, int y) {
  mPos.x = x;
  mPos.y = y;
}

void Player::handleXCollisions(const vector<AABBCollider*>& colliders) {
  if (colliders.empty()) return;

  int greatestIndex = -1;

  for (int i = 0; i < colliders.size(); i++) {
    if (!colliders.at(i)->isTrigger()) {
      double greatest = 0;

      double temp = getInterArea(*colliders.at(i));
      if (temp > greatest) {
        greatestIndex = i;
        greatest = temp;
      }

      colliders.at(i)->handleCollisions(this);
    }
  }

  if (greatestIndex >= 0)
    mPos.x = mPos.x + getProjectionVector(*colliders.at(greatestIndex)).x;
}

void Player::handleYCollisions(const vector<AABBCollider*>& colliders) {
  int greatestIndex = -1;
  if (colliders.empty()) {
    grounded = false;
    return;
  }

  for (int i = 0; i < colliders.size(); i++) {
    if (!colliders.at(i)->isTrigger()) {
      double greatest = 0;

      double temp = getInterArea(*colliders.at(i));
      if (temp > greatest) {
        greatestIndex = i;
        greatest = temp;
      }
    }
    colliders.at(i)->handleCollisions(this);
    handleCollisions(colliders.at(i));
  }

  if (greatestIndex >= 0) {
    AABBCollider* greatestCollider = colliders.at(greatestIndex);
    int collidedPosition = getCollidedPosition(*greatestCollider);
    if (velocity.y > 0 &&
        (collidedPosition == top_left || collidedPosition == top_right)) {
      grounded = true;
      velocity.y = 0;
      canJump = true;
    } else {
      grounded = false;
    }

    // hit bottom of object
    if (velocity.y < 0 &&
        (getCollidedPosition(*greatestCollider) == bottom_left ||
         getCollidedPosition(*greatestCollider) == bottom_right)) {
      velocity.y = 0;
    }

    mPos.y = mPos.y + getProjectionVector(*colliders.at(greatestIndex)).y;
  }
}

void Player::handleCollisions(AABBCollider* collider) {}

void Player::handleTrigger(const std::string& name) {}