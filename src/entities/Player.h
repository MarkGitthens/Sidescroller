#pragma once
#include <string>

#include "core/AnimatedSprite.h"
#include "core/Entity.h"
#include "core/Game.h"
#include "core/events/KeyboardEvent.h"
#include "physics/AABBCollider.h"
#include "Projectile.h"

class PlayerState;
class PlayerIdle;
class PlayerWalk;
class PlayerJump;

const int speed = 8;

// TODO: Entities shouldn't inherit AABBCollider since a single entity have
// multiple colliders
class Player : public Vulture2D::Entity,
               public AABBCollider,
               public Vulture2D::AnimatedSprite {
 public:
  Player(){};
  Player(int, int, int, int);
  virtual ~Player();

  virtual void start();
  virtual void update();
  virtual void stop();
  void handleInput(Event *);

  void handleXCollisions(const vector<AABBCollider *> &);
  void handleYCollisions(const vector<AABBCollider *> &);
  virtual void handleCollisions(AABBCollider *);
  virtual void handleTrigger(const std::string &);

  virtual void render(SDL_Rect *);

  void setPosition(int x, int y);

  void fireBullet();

 protected:
  friend class PlayerState;
  friend class PlayerIdle;
  friend class PlayerWalk;
  friend class PlayerJump;

  PlayerIdle* _PlayerIdleState;
  PlayerWalk* _PlayerWalkState;
  PlayerJump* _PlayerJumpState;

  bool canJump = true;
  bool grounded = false;
  bool facingLeft = false;
  PlayerState *state = nullptr;

  vector<int> registeredCallbacks;
};