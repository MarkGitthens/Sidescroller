#include "Game.h"

namespace Vulture2D {
void Game::init() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cerr << "SDL could not initialize!\n" << SDL_GetError() << std::endl;
  }
  if (IMG_Init(IMG_INIT_PNG) < 0) {
    std::cerr << "SDL_Img could not be initialized!\n"
              << IMG_GetError() << std::endl;
  }

  window =
      SDL_CreateWindow("Sidescroller", SDL_WINDOWPOS_UNDEFINED,
                       SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);

  Renderer::getInstance().init(window, SDL_RENDERER_ACCELERATED);

  screenSurface = SDL_GetWindowSurface(window);

  InputHandler::getInstance();
  SoundMixer::getInstance();

  AssetManager::getInstance();
  SceneHandler::getInstance();

  running = true;
}

void Game::run() {
  // TODO: Should probably create a timer class to keep track of time instead of
  // just always using SDL_GetTicks() and doing the checks
  double deltaTime = 16.667;

  double currentTime = SDL_GetTicks();
  double backlog = 0;

  int fpsCounter = 0;
  int updateCounter = 0;

  double fpsTimerStart = SDL_GetTicks();

  while (running) {
    double newTime = SDL_GetTicks();
    double frameTime = newTime - currentTime;

    currentTime = newTime;
    backlog += frameTime;
    InputHandler::getInstance().handleInput();
    SoundMixer::getInstance().updateSound();
    sendInputEvents();

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
    }

    SceneHandler::getInstance().getCurrentScene()->renderScene();
    fpsCounter++;

    if (InputHandler::getInstance().actionHeld("quit_game")) running = false;
  }
}

void Game::sendInputEvents() {
  vector<int> pressed = InputHandler::getInstance().getPressedKeys();
  vector<int> held = InputHandler::getInstance().getHeldKeys();
  vector<int> released = InputHandler::getInstance().getReleasedKeys();

  Scene* currentScene = SceneHandler::getInstance().getCurrentScene();
  for (auto p : pressed) {
    KeyboardEvent event(KeyboardEvent::KeyPress, p);
    currentScene->dispatchEvent(&event);
  }

  for (auto h : held) {
    KeyboardEvent event(KeyboardEvent::KeyHeld, h);
    currentScene->dispatchEvent(&event);
  }

  for (auto r : released) {
    KeyboardEvent event(KeyboardEvent::KeyReleased, r);
    currentScene->dispatchEvent(&event);
  }
}

Renderer& Game::getRenderer() { return Renderer::getInstance(); }

SDL_Renderer* Game::getSDLRenderer() {
  return Renderer::getInstance().getRenderer();
}

SceneHandler& Game::getSceneHandler() { return SceneHandler::getInstance(); }

InputHandler& Game::getInputHandler() { return InputHandler::getInstance(); }

AssetManager& Game::getAssetManager() { return AssetManager::getInstance(); }

SoundMixer& Game::getSoundMixer() { return SoundMixer::getInstance(); }

void Game::registerInputs() {
  InputHandler::getInstance().addKeyAction(SDLK_ESCAPE, "quit_game");
  InputHandler::getInstance().addKeyAction(SDLK_RIGHT, "move_right");
  InputHandler::getInstance().addKeyAction(SDLK_LEFT, "move_left");
  InputHandler::getInstance().addKeyAction(SDLK_t, "test_scene");
  InputHandler::getInstance().addKeyAction(SDLK_SPACE, "jump");
}

void Game::destroy() {
  AssetManager::destroy();
  SceneHandler::destroyInstance();

  SDL_FreeSurface(screenSurface);
  screenSurface = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}
}  // namespace Vulture2D