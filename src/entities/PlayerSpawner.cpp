#include "PlayerSpawner.h"

PlayerSpawner::PlayerSpawner(int x, int y) {
  this->x = x;
  this->y = y;
}

void PlayerSpawner::lateStart() {
  spawnPlayer(nullptr);
  Callback spawn = [this](Event* e) { this->spawnPlayer(e); };

  Game::getSceneHandler().getCurrentScene()->addListener(
      KeyboardEvent::KeyPress, spawn);
}

void PlayerSpawner::spawnPlayer(Event* e) {
  KeyboardEvent* k = (KeyboardEvent*)e;

  if (!player) {
    Scene* scene = Game::getSceneHandler().getCurrentScene();
    player = new Player(x, y + 64, 64, 64);
    player->setName("player");
    player->setSprite(Game::getAssetManager().getTexture("player"));

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;

    camera = new Camera();
    camera->setSceneWidth(scene->getSceneWidth());
    camera->setSceneHeight(scene->getSceneHeight());
    camera->setCameraRect(cameraRect);

    player->start();
    scene->registerEntity(player);
    camera->setParentPos(player->getPos());
    scene->setCamera(camera);
  }

  if (!e) {
    return;
  }
  if (k->keyID == SDLK_r) {
    player->setVelocity(player->getVelocity().x, 0);
    player->setPosition(x, y + 64);
  }
}