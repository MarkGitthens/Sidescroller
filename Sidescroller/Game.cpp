#include "Game.h"

namespace Vulture2D {
    void Game::init() {
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
    }

    void Game::run() {

    }

    void Game::destroy() {

    }
}