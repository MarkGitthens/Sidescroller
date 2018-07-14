#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"
#include "InputHandler.h"
#include "SceneHandler.h"

namespace Vulture2D {
    class Game {
    public:
        Game() {}
        void init();
        void run();
        static SDL_Renderer* getRenderer();
        static SceneHandler& getSceneHandler();
        static InputHandler& getInputHandler();
        void sendInputEvents();
        void registerInputs();
        void destroy();
        
    private:
        SDL_Window * window;
        SDL_Surface* screenSurface;
        bool running = false;
    };
}