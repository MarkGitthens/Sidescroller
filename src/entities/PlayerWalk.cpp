#include "PlayerWalk.h"

#include "Player.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"

PlayerWalk::PlayerWalk(Player *player) {
  
}
void PlayerWalk::enter(Player *player) {player->setAnimation("player_walking");}

void PlayerWalk::exit(Player *player) {}

PlayerState *PlayerWalk::update(Player *player) {
  PlayerState::update(player);

  if (fabs(player->velocity.x) <= .001f) {
    return player->_PlayerIdleState;
  }

  if (!player->grounded) {
    return player->_PlayerJumpState;
  }

  return nullptr;
}

PlayerState *PlayerWalk::handleInput(Player *player, Event *event) {
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