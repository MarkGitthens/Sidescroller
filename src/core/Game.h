#pragma once

#include <SDL.h>
#include "Renderer.h"
#include <SDL_image.h>

#include "InputHandler.h"
#include "SceneHandler.h"

namespace Vulture2D {
    class Game {
    public:
        void init();
        void run();
        void registerInputs();
        void destroy();
        
    private:
        SDL_Window * window;
        SDL_Surface* screenSurface;
        bool running = false;
    };
}