#include "core/Game.h"

#include "entities/Player.h"
#include "entities/Box.h"
#include "entities/Camera.h"
#include "entities/ResetBox.h"

#include "util/tiled/TiledParser.h"

using namespace Vulture2D;

//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();

Player* player;
Camera* camera;

ResetBox* reset;
Scene scene;

Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game();

    game->init();
    game->registerInputs();

    scene.setName("start");
    SceneHandler::getInstance().registerScene(&scene);
    
    initializeEntities();
    
    scene.registerEntity(player);
    scene.setCamera(camera);
    scene.registerEntity(reset); 

    game->run();
    game->destroy();

    return 0;
}



void initializeEntities() {
    player = new Player(64, 300, 64, 64);
    player->setName("Player");
    player->createFromPath("resources/images/MyChar.png", game->getSDLRenderer());
    player->setFrameCount(3);
    player->setFrameDelay(5);
    player->setFrameDimensions(16, 16);

    TiledParser::parse("Level1.tmx", "resources/tilesets/", &scene);

    reset = new ResetBox(-1000, 1500, 10000, 128);
    reset->setName("reset_box");
    reset->setTrigger(true);

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;

    camera = new Camera();
    camera->setSceneWidth(scene.getSceneWidth());
    camera->setSceneHeight(scene.getSceneHeight());
    camera->setCameraRect(cameraRect);
    camera->setParentPos(player->getPos());
}
