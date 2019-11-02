#pragma once

#include "PlayerState.h"

class PlayerIdle : public PlayerState {
 public:
  PlayerIdle(Player* player);
  void enter(Player *player);
  void exit(Player *player);
  PlayerState *update(Player *player);
  PlayerState *handleInput(Player *player, Event *event);
};