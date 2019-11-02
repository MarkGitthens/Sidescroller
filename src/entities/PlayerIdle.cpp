#include "PlayerIdle.h"

#include "Player.h"
#include "PlayerJump.h"
#include "PlayerWalk.h"

PlayerIdle::PlayerIdle(Player *player) { }
void PlayerIdle::enter(Player *player) {player->setAnimation("player_idle"); }

void PlayerIdle::exit(Player *player) {}

PlayerState *PlayerIdle::update(Player *player) {
  PlayerState::update(player);
  if (fabs(player->velocity.x) >= .001f) return player->_PlayerWalkState;

  if (!player->grounded) {
    return player->_PlayerJumpState;
  }
  return nullptr;
}

PlayerState *PlayerIdle::handleInput(Player *player, Event *event) {
  PlayerState::handleInput(player, event);
  KeyboardEvent *e = (KeyboardEvent *)event;
  if (event->getType() == KeyboardEvent::KeyPress) {
    if (e->keyID == SDLK_SPACE) {
      player->velocity.y = -30;
      return player->_PlayerJumpState;
    }
  }

  return nullptr;
}