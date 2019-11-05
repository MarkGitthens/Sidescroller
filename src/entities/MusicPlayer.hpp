#pragma once
#include <string>

#include "core/Entity.h"
#include "core/Game.h"
#include "core/Sound.h"

using std::string;
using namespace Vulture2D;

class MusicPlayer : public Entity {
 public:
  MusicPlayer(int x, int y, string music)
      : channel(-1), sound(Game::getAssetManager().getSound(music)) {
    this->x = x;
    this->y = y;
  }
  
  ~MusicPlayer() {}

  void start();
  void update();
  void stop();

 private:
  Sound sound;
  int channel;
};