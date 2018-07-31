#pragma once
#include "../core/Entity.h"
#include "../entities/Player.h"
#include "../core/Game.h"
#include "../core/events/KeyboardEvent.h"
#include "../entities/Camera.h"

using namespace Vulture2D;
class PlayerSpawner: public Entity {
public:
    PlayerSpawner(Camera* camera, int x = 0, int y = 0) : camera(camera) {
        this->x = x;
        this->y = y;

        Callback spawn = [this](Event* e) {
            this->spawnPlayer(e);
        };

        Game::getSceneHandler().getCurrentScene()->addListener(KeyboardEvent::KeyPress, spawn);
    }

    virtual void update() {};
    void spawnPlayer(Event*);

private:
    Player* player = nullptr;
    Camera* camera = nullptr;
};