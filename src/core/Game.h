#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"
#include "InputHandler.h"
#include "SceneHandler.h"
//#include "AssetPool.h"

namespace Vulture2D {
    class Game {
    public:
        Game() {}
        void init();
        void run();
        static SDL_Renderer* getSDLRenderer();
        static Renderer& getRenderer();
        static SceneHandler& getSceneHandler();
        static InputHandler& getInputHandler();
        static AssetPool& getAssetPool();
        void sendInputEvents();
        void registerInputs();
        void destroy();
        
    private:
        SDL_Window * window;
        SDL_Surface* screenSurface;
        bool running = false;
    };
}