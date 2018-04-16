#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>
#include "SDL_mixer.h"

#include "InputHandler.h"
#include "SceneHandler.h"

#include "Player.h"
#include "Box.h"
#include "Scene.h"
#include "Audio.h"

void initializeEntities();
bool initializeAudio();
void registerInputs();
void shutdown();

//SDL specific pointers
SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr;

//Entities
Player* player;
Box* box;
Box* box2;
Box* box3;
Box* box4;
Box* box5;
Box* box6;
Box* box7;
TiledMap* map;
Camera* camera;

Scene scene;

bool running = true;

// SDL Music
Music* music = nullptr;

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        //error
        std::cerr << "SDL could not initialize!\n" << SDL_GetError() << std::endl;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "SDL_Img could not be initialized!\n" << IMG_GetError() << std::endl;
    }

    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cerr << "SDL_mixer could not initialize!\n" << Mix_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenSurface = SDL_GetWindowSurface(window);

    
    initializeEntities();
    initializeAudio();
    registerInputs();

    scene.setName("start");
    scene.setTiledMap(map);
    scene.registerEntity(player);

    //scene.registerEntity(box);
    scene.registerEntity(box2);
    scene.registerEntity(box3);
    scene.registerEntity(box4);
    scene.registerEntity(box5);
    scene.registerEntity(box6);
    scene.registerEntity(box7);

    scene.setCamera(camera);

    scene.initThreads();
    music->subscribeToEvents();
    
    Scene testScene;
    testScene.setName("test_scene");
    testScene.registerEntity(player);
    testScene.setCamera(camera);
    testScene.setTiledMap(map);

    SceneHandler::getInstance().registerScene(&scene);
    SceneHandler::getInstance().registerScene(&testScene);
    //Should probably create a timer class to keep track of time instead of just always using SDL_GetTicks() and doing the checks manually
    double deltaTime = 16.667;

    double currentTime = SDL_GetTicks();
    double backlog = 0;

    int fpsCounter = 0;
    int updateCounter = 0;

    double fpsTimerStart = SDL_GetTicks();
    double updateTimerStart = SDL_GetTicks();

    while (running) {
        double newTime = SDL_GetTicks();
        double frameTime = newTime - currentTime;

        currentTime = newTime;
        backlog += frameTime;

        InputHandler::getInstance().handleInput();

        while (backlog >= deltaTime) {
            SceneHandler::getInstance().getCurrentScene()->updateScene();
            backlog -= deltaTime;
            updateCounter++;
        }
        if ((currentTime - fpsTimerStart) >= 1000) {
            std::cout << fpsCounter << " " << updateCounter << std::endl;
            fpsCounter = 0;
            updateCounter = 0;
            fpsTimerStart = currentTime;
            updateTimerStart = currentTime;
        }


        SceneHandler::getInstance().getCurrentScene()->renderScene();
        fpsCounter++;
    }

	shutdown();
    return 0;
}

void quitGame(int a) {
	running = false;
}
void shutdown() {
    SDL_FreeSurface(screenSurface);
    screenSurface = nullptr;

    SDL_DestroyWindow(window);
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

bool initializeAudio() {
    bool good = true;
    music = new Music("background_music");
    good = music->load("audio/beat.wav");
    return good;
}

void initializeEntities() {
    player = new Player(64, 300, 64, 64);

    player->setName("Player");
    player->createFromPath("images/ball.png");

    //box = new Box(0, 0, 128, 128);
    //box->setName("Box");
    //box->setTrigger(true);
    //box->createFromPath("images/block.png");

    box2 = new Box(128, 0, 128, 128);
    box2->setName("Box2");
    box2->createFromPath("images/block.png");

    box3 = new Box(256, 0, 128, 128);
    box3->setName("Box3");
    box3->createFromPath("images/block.png");

    box4 = new Box(256, -128, 128, 128);
    box4->setName("Box4");
    box4->createFromPath("images/block.png");

    box5 = new Box(128, -256, 128, 128);
    box5->setName("Box5");
    box5->createFromPath("images/block.png");

    box6 = new Box(0, -256, 128, 128);
    box6->setName("Box6");
    box6->createFromPath("images/block.png");
    box6->setTrigger(true);

    box7 = new Box(0, 74, 10, 10);
    box7->setName("Box7");
    box7->createFromPath("images/block.png");

    map = new TiledMap(15,10,128,128);
    map->setTileSheet("images/tilesheet_complete_2X.png");
    map->parseFile("tilesets/Level1.tmx");

    camera = new Camera();

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;
    camera->setCameraRect(cameraRect);
    camera->setParentPos(player->getPos());
}

void registerInputs() {
    InputHandler::getInstance().addKeyAction(SDLK_ESCAPE, "quit_game");
	EventHandler::getInstance().subscribeToEvent("quit_game", "main", std::bind(quitGame, std::placeholders::_1));
    InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
    InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
    InputHandler::getInstance().addKeyAction(SDLK_UP, "move_up");
    InputHandler::getInstance().addKeyAction(SDLK_DOWN, "move_down");
    InputHandler::getInstance().addKeyAction(SDLK_t, "test_scene");
	InputHandler::getInstance().addKeyAction(SDLK_SPACE, "fire_bullet");

    InputHandler::getInstance().addKeyAction(SDLK_d, "delete_box");

    InputHandler::getInstance().addKeyAction(SDLK_m, music->getMuteActionName());
    InputHandler::getInstance().addKeyAction(SDLK_MINUS, music->getVolumeLowerActionName());
    InputHandler::getInstance().addKeyAction(SDLK_EQUALS, music->getVolumeHigherActionName());
}