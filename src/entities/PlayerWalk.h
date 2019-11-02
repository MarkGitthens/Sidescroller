#pragma once

#include "PlayerState.h"


class PlayerWalk : public PlayerState {
 public:
  PlayerWalk(Player* player);
  void enter(Player *player);
  void exit(Player *player);
  PlayerState *update(Player *player);
  PlayerState *handleInput(Player *player, Event *event);
};