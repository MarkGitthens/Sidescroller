#pragma once
#include <SDL.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "EventHandler.h"
#include "KeyboardEvent.h"

namespace Vulture2D {
    class InputHandler {
    public:
        static InputHandler& getInstance();

        void handleInput();
        void addKeyAction(int key, std::string tag);
        void removeKeyAction(int key);
        bool actionTriggered(const std::string& action);
        bool actionHeld(const std::string& action);

        bool keyHeld(int key);
        bool keyPressed(int key);
        bool keyReleased(int key);

        vector<int> getPressedKeys();
        vector<int> getHeldKeys();
        vector<int> getReleasedKeys();

    private:
        ~InputHandler() { if (instance) { delete instance; } instance = nullptr; }
        InputHandler() {}

        SDL_Event mEvent;
        static InputHandler* instance;

        std::unordered_map<int, bool> mPressedKeys;
        std::unordered_map <int, bool> mHeldKeys;
        std::unordered_map <int, bool> mReleasedKeys;

        std::unordered_map<int, std::string> mKeyMap;
        std::unordered_map<std::string, int> mActionMap;
    };
}