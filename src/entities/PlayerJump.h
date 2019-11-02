#pragma once
#include "PlayerState.h"

class PlayerJump : public PlayerState {
 public:
  PlayerJump(Player* player);
  void enter(Player *player);
  void exit(Player *player);
  PlayerState *update(Player *player);
  PlayerState *handleInput(Player *player, Event *event);

 private:
  int numJumps = 2;
  int jumpCount = 1;
};