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
#include "ResetBox.h"

#include "TiledParser.h"

//TODO: Should define a consistent unit of measurement instead of just using pixel size
void initializeEntities();
bool initializeAudio();
void registerInputs();
void shutdown();

//SDL specific pointers
SDL_Window* window = nullptr;
SDL_Surface* screenSurface = nullptr;

//Entities
Player* player;
Camera* camera;

ResetBox* reset;
Scene scene;

bool running = true;

// SDL Music
Music* music = nullptr;

int main(int argc, char* argv[]) {
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize!\n" << SDL_GetError() << std::endl;
    }
    if (IMG_Init(IMG_INIT_PNG) < 0) {
        std::cerr << "SDL_Img could not be initialized!\n" << IMG_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize!\n" << Mix_GetError() << std::endl;
    }

    window = SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

    Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenSurface = SDL_GetWindowSurface(window);

    initializeEntities();
    initializeAudio();
    registerInputs();

    scene.setName("start");
    scene.registerEntity(player);
    scene.setCamera(camera);

    scene.initThreads();
    music->subscribeToEvents();
    
    scene.registerEntity(reset);

    SceneHandler::getInstance().registerScene(&scene);

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
    SceneHandler::getInstance().getCurrentScene()->destroy();

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
    //TODO: Should probably make player a unique entity that will only ever have one copy
    player = new Player(64, 300, 64, 64);

    player->setName("Player");
    player->createFromPath("images/ball.png");

    TiledParser::parse("Level1.tmx", "tilesets/", &scene);

    camera = new Camera();

    reset = new ResetBox(-1000, 1500, 10000, 128);
    reset->setName("reset_box");
    reset->setTrigger(true);

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1280;
    cameraRect->h = 720;
    camera->setCameraRect(cameraRect);
    camera->setParentPos(player->getPos());
}

void registerInputs() {
    //TODO: Should really verify this is how I actually want InputHandler and EventHandler to work.
    InputHandler::getInstance().addKeyAction(SDLK_ESCAPE, "quit_game");
	EventHandler::getInstance().subscribeToEvent("quit_game", "main", std::bind(quitGame, std::placeholders::_1));
    InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
    InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
    InputHandler::getInstance().addKeyAction(SDLK_t, "test_scene");
	InputHandler::getInstance().addKeyAction(SDLK_SPACE, "jump");

    InputHandler::getInstance().addKeyAction(SDLK_m, music->getMuteActionName());
    InputHandler::getInstance().addKeyAction(SDLK_MINUS, music->getVolumeLowerActionName());
    InputHandler::getInstance().addKeyAction(SDLK_EQUALS, music->getVolumeHigherActionName());
}