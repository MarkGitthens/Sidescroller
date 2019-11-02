#pragma once
#include "../core/Entity.h"
#include "../entities/Player.h"
#include "../core/Game.h"
#include "../core/events/KeyboardEvent.h"
#include "../entities/Camera.h"
#include <iostream>

using namespace Vulture2D;
class PlayerSpawner: public Entity {
public:
    PlayerSpawner(int, int);

    virtual void update() {};
    void spawnPlayer(Event*);
    virtual void start();

private:
    Player* player = nullptr;
    Camera* camera = nullptr;
};