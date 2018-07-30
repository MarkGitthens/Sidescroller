#pragma once
#include "../core/Game.h"
#include "../core/Renderable.h"
#include "../core/Entity.h"
#include "../physics/AABBCollider.h"

class BreakableBox: public Entity, public Renderable, public AABBCollider {
public:
    BreakableBox();
    BreakableBox(SDL_Rect dimensions);
    BreakableBox(int, int, int, int);

    virtual void update() {};
    virtual void handleCollisions();
    virtual void render(SDL_Rect*);

    void setContains(Entity*);

private:
    void loadSheetPosition() {
        image = Game::getAssetManager().getTexture("tilesheet");
        sheetPosition.x = 16 * 128;
        sheetPosition.y = 9 * 128;
        sheetPosition.w = 128;
        sheetPosition.h = 128;

        sound = new Sound(Game::getAssetManager().getSound("break_block"));
    }

    Sound* sound;
    Entity* contains = nullptr;
    SDL_Rect sheetPosition;
};