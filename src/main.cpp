#include "core/Game.h"
#include "util/tiled/TiledParser.h"

#include "tests/Collision_test.h"
#include "tests/Vector2D_test.h"

using namespace Vulture2D;

//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();
void registerAssets();

Scene scene;
Scene testScene;

Game* game = nullptr;

int main(int argc, char* argv[]) {

    Collision_test collisionsTest;
    Vector2D_test vectorTest;

    if(!vectorTest.run() || !collisionsTest.run()) {
        return -1;
    }

    game = new Game();
    
    game->init();
    game->registerInputs();

    registerAssets();
    initializeEntities();

    scene.setName("start");
    testScene.setName("testScene");

    SceneHandler::getInstance().registerScene(&scene);
    SceneHandler::getInstance().registerScene(&testScene);

    SceneHandler::getInstance().changeScene("start");

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
    pool.createTexture("resources/images/Bone.png", "coin", Game::getSDLRenderer());
    pool.createSound("resources/audio/Off_Limits.wav", "bgMusic");
    pool.createSound("resources/audio/low.wav", "bullet");
    pool.createSound("resources/audio/block_break.wav", "break_block");

}

void initializeEntities() {
    TiledParser::parse("Level1.tmx", "resources/tilesets/", &scene);
    TiledParser::parse("Level2.tmx", "resources/tilesets/", &testScene);
}
