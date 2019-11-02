#include "PlayerWalk.h"

#include "Player.h"
#include "PlayerIdle.h"
#include "PlayerJump.h"

PlayerWalk::PlayerWalk(Player *player) {
  player->setAnimation("player_walking");
}
void PlayerWalk::enter(Player *player) {}

void PlayerWalk::exit(Player *player) {}

PlayerState *PlayerWalk::update(Player *player) {
  PlayerState::update(player);

  if (fabs(player->velocity.x) <= .001f) {
    return new PlayerIdle(player);
  }

  if (!player->grounded) {
    return new PlayerJump(player);
  }

  return nullptr;
}

PlayerState *PlayerWalk::handleInput(Player *player, Event *event) {
  PlayerState::handleInput(player, event);
  KeyboardEvent *e = (KeyboardEvent *)event;
  if (event->getType() == KeyboardEvent::KeyPress) {
    if (e->keyID == SDLK_SPACE) {
      player->velocity.y = -30;
      return new PlayerJump(player);
    }
  }
  return nullptr;
}