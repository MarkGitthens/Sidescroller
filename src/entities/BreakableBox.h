#pragma once
#include "../core/Game.h"
#include "../core/Renderable.h"
#include "../core/Entity.h"
#include "../physics/AABBCollider.h"

class BreakableBox: public Entity, public Renderable, public AABBCollider {
public:
    BreakableBox(): sound(Game::getAssetManager().getSound("break_block")){
        loadSheetPosition();
    }

    BreakableBox(SDL_Rect dimensions): sound(Game::getAssetManager().getSound("break_block")) {
        mPos.x = dimensions.x;
        mPos.y = dimensions.y;
        mHalfWidth = dimensions.w / 2;
        mHalfHeight = dimensions.h / 2;

        loadSheetPosition();
    }

    BreakableBox(int x, int y, int w, int h): sound(Game::getAssetManager().getSound("break_block")) {
        mPos.x = x;
        mPos.y = y;

        mHalfHeight = h / 2;
        mHalfWidth = w / 2;

        loadSheetPosition();
    }

    ~BreakableBox() {
        if(!destroyed)
            delete contains;
    }

    virtual void update() {};
    virtual void handleCollisions(AABBCollider*);
    virtual void render(SDL_Rect*);

    void setContains(Entity*);

private:
    void loadSheetPosition() {
        image = Game::getAssetManager().getTexture("tilesheet");
        sheetPosition.x = 16 * 128;
        sheetPosition.y = 9 * 128;
        sheetPosition.w = 128;
        sheetPosition.h = 128;
    }

    bool destroyed = false;
    Sound sound;
    Entity* contains = nullptr;
    SDL_Rect sheetPosition;
};