#pragma once
#include "../core/events/Event.h"

class Player;

using Vulture2D::Event;
class PlayerState {
 public:
  PlayerState();
  virtual void enter(Player *player);
  virtual void exit(Player *player);
  virtual PlayerState *update(Player *player);
  virtual PlayerState *handleInput(Player *player, Event *event);
};