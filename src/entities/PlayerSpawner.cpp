#include "PlayerSpawner.h"

void PlayerSpawner::spawnPlayer(Event* e) {
    KeyboardEvent* k = (KeyboardEvent*) e;

    if(k->keyID == SDLK_r) {
        Scene* scene = Game::getSceneHandler().getCurrentScene();
        if(!player) {
            player = new Player(x, y, 64, 64);
            player->setName("player");
            player->setSprite(Game::getAssetManager().getTexture("player"));

            scene->registerEntity(player);
            camera->setParentPos(player->getPos());
            scene->setCamera(camera);

        } else {
            player->setVelocity(0, 0);
            player->setPosition(x, y);
        }
    }
}