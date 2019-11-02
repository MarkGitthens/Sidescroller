#include "PlayerJump.h"

#include "Player.h"
#include "PlayerIdle.h"

PlayerJump::PlayerJump(Player *player) {}
void PlayerJump::enter(Player *player) {
  jumpCount = 1;
  player->grounded = false;
  player->setAnimation("player_jump");
}

void PlayerJump::exit(Player *player) { jumpCount = 1; }

PlayerState *PlayerJump::update(Player *player) {
  PlayerState::update(player);
  if (player->grounded) {
    return player->_PlayerIdleState;
  }
  return nullptr;
}

PlayerState *PlayerJump::handleInput(Player *player, Event *event) {
  PlayerState::handleInput(player, event);
  KeyboardEvent *e = (KeyboardEvent *)event;
  if (event->getType() == KeyboardEvent::KeyPress) {
    if (e->keyID == SDLK_SPACE) {
      if (jumpCount < numJumps) {
        jumpCount++;
        player->velocity.y = -30;
      }
    }
  }

  return nullptr;
}
