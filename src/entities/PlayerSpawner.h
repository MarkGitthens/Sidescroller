#pragma once
#include <iostream>

#include "core/Entity.h"
#include "core/Game.h"
#include "core/events/KeyboardEvent.h"
#include "entities/Camera.h"
#include "entities/Player.h"

using namespace Vulture2D;
class PlayerSpawner : public Entity {
 public:
  PlayerSpawner(int, int);

  virtual void update(){};
  void spawnPlayer(Event*);
  virtual void lateStart();

 private:
  Player* player = nullptr;
  Camera* camera = nullptr;
};