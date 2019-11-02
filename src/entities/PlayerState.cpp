#include "PlayerState.h"

#include "Player.h"
#include "PlayerJump.h"

PlayerState::PlayerState() {}

void PlayerState::enter(Player *player) {}

void PlayerState::exit(Player *player) {}

PlayerState *PlayerState::update(Player *player) {
  int gravity = 1;

  if (player->velocity.y < 30) player->velocity.y += gravity;

  if (player->velocity.x < 0)
    player->facingLeft = true;
  else if (player->velocity.x > 0)
    player->facingLeft = false;

  player->mPos.x += player->velocity.x;
  player->handleXCollisions(
      Game::getSceneHandler().getCurrentScene()->checkCollisions(player));

  player->mPos.y += player->velocity.y;
  player->handleYCollisions(
      Game::getSceneHandler().getCurrentScene()->checkCollisions(player));

  return nullptr;
}

PlayerState *PlayerState::handleInput(Player *player, Event *event) {
  KeyboardEvent *e = (KeyboardEvent *)event;
  if (event->getType() == KeyboardEvent::KeyPress) {
    if (e->keyID == SDLK_e) {
      player->fireBullet();
    }

    if(e->keyID == SDLK_l) {
        SceneHandler::getInstance().changeScene("testScene");
    }

    if (e->keyID == SDLK_RIGHT) {
      player->velocity.x += speed;
    } else if (e->keyID == SDLK_LEFT) {
      player->velocity.x += -speed;
    }
  }

  if (event->getType() == KeyboardEvent::KeyReleased) {
    
    
    if (e->keyID == SDLK_RIGHT) {
      player->velocity.x -= speed;
    }

    if (e->keyID == SDLK_LEFT) {
      player->velocity.x -= -speed;
    }
  }

  return nullptr;
}