#include "core/Game.h"
#include "util/tiled/TiledParser.h"

using namespace Vulture2D;

//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();
void registerAssets();

Scene scene;
Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();
    
    game->init();
    game->registerInputs();

    registerAssets();
    scene.setName("start");
    SceneHandler::getInstance().registerScene(&scene);
    
    initializeEntities();

    game->run();
    game->destroy();
    return 0;
}

void registerAssets() {
    AssetManager& pool = Game::getAssetManager();

    pool.createTexture("resources/images/MyChar.png", "player", Game::getSDLRenderer());
    pool.createTexture("resources/images/block.png", "block", Game::getSDLRenderer());
    pool.createTexture("resources/images/ball.png", "crab", Game::getSDLRenderer());
    pool.createTexture("resources/tilesets/tilesheet_complete_2X.png", "tilesheet", Game::getSDLRenderer());
    pool.createSound("resources/audio/Off_Limits.wav", "bgMusic");
    pool.createSound("resources/audio/low.wav", "bullet");
    pool.createSound("resources/audio/block_break.wav", "break_block");

}

void initializeEntities() {
    TiledParser::parse("Level1.tmx", "resources/tilesets/", &scene);
}
