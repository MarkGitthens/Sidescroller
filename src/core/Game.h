#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "Renderer.h"
#include "InputHandler.h"
#include "SceneHandler.h"
#include "AssetManager.h"
#include "SoundMixer.h"

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
        static AssetManager& getAssetManager();
        static SoundMixer& getSoundMixer();
        void sendInputEvents();
        void registerInputs();
        void destroy();
        
    private:
        SDL_Window * window = nullptr;
        SDL_Surface* screenSurface = nullptr;
        bool running = false;
    };
}