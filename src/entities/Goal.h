#pragma once

#include "../core/Entity.h"
#include "../physics/AABBCollider.h"
#include "../core/Renderable.h"
#include "../entities/Player.h"

using namespace Vulture2D;

class Goal : public Entity, public AABBCollider, public Renderable {
public:
    Goal(int x=0, int y=0, int width=50, int height=50, std::string scene = "default");
    ~Goal() {};

    void update() {};
    void handleCollisions(AABBCollider*);
    void handleTrigger(const std::string&) {};

    void render(SDL_Rect*);


private:
    std::string nextScene;
};