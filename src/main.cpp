#include "core/Game.h"

#include "entities/Player.h"
#include "entities/PlayerSpawner.h"
#include "entities/Box.h"
#include "entities/Camera.h"

#include "util/tiled/TiledParser.h"

using namespace Vulture2D;

//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();
void registerAssets();

PlayerSpawner* spawner;
Camera* camera;

Box* reset;
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
    
    scene.registerEntity(spawner);

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

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;

    camera = new Camera();
    camera->setSceneWidth(scene.getSceneWidth());
    camera->setSceneHeight(scene.getSceneHeight());
    camera->setCameraRect(cameraRect);

    spawner = new PlayerSpawner(camera, 64, 1000);
}
