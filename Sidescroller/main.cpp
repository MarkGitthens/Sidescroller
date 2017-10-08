#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>
#include "SDL_mixer.h"

#include "InputHandler.h"

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
    if (IMG_Init(IMG_INIT_PNG)) {

    }

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "SDL_mixer could not initialize!\n" << Mix_GetError() << std::endl;
	}

    window = SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1080, SDL_WINDOW_SHOWN);

    Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    screenSurface = SDL_GetWindowSurface(window);

    
    initializeEntities();
	initializeAudio();
	registerInputs();

    scene.setTiledMap(map);
    scene.registerEntity(player);
	scene.registerOffScreenEntity(music);
    scene.setCamera(camera);

	scene.initThreads();
    while (!InputHandler::getInstance().actionTriggered("SDL_QUIT")) {
        InputHandler::getInstance().handleInput();
        scene.updateScene();
    }

    shutdown();
    return 0;
}

void shutdown() {
	scene.stopThreads();
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
    player = new Player();

    player->setName("Player");
    player->createFromPath("images/ball.png");
    player->setPosition(0, 0);
    player->setLayer(1);
    map = new TiledMap(15,10,128,128);
    map->setTileSheet("images/tilesheet_complete_2X.png");
    map->parseFile("tilesets/Level1.tmx");

    camera = new Camera();

    SDL_Rect* cameraRect = new SDL_Rect();
    cameraRect->x = 0;
    cameraRect->y = 0;
    cameraRect->w = 1920;
    cameraRect->h = 1080;
    camera->setCameraRect(cameraRect);
    camera->setParentRect(player->getRenderRect());
}

void registerInputs() {
	InputHandler::getInstance().addKeyAction(SDLK_ESCAPE, "SDL_QUIT");
	InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
    InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
    InputHandler::getInstance().addKeyAction(SDLK_UP, "move_up");
    InputHandler::getInstance().addKeyAction(SDLK_DOWN, "move_down");
	InputHandler::getInstance().addKeyAction(SDLK_m, music->getMuteActionName());
	InputHandler::getInstance().addKeyAction(SDLK_MINUS, music->getVolumeLowerActionName());
	InputHandler::getInstance().addKeyAction(SDLK_EQUALS, music->getVolumeHigherActionName());
}