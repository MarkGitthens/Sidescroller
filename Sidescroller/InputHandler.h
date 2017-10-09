#pragma once
#include <SDL.h>
#include <string>
#include <unordered_map>

#include "EventHandler.h"
#include "Entity.h"

class InputHandler {
public:
    static InputHandler& getInstance();
    void handleInput();
    void addKeyAction(int key, std::string tag);
    void removeKeyAction(int key);
    bool actionTriggered(std::string action);
    bool actionPressTriggered(std::string action);
private:
    ~InputHandler() { if (instance) { delete instance; } instance = nullptr; }
    InputHandler() { mTriggeredActions["SDL_QUIT"] = false; }
    InputHandler(InputHandler const&) {}
    InputHandler& operator=(InputHandler const& e) {}

    SDL_Event mEvent;
    static InputHandler* instance;
    std::unordered_map<std::string, bool> mTriggeredActions;
    std::unordered_map<std::string, int> mPressedTriggeredActions;
    std::unordered_map<std::string, int> mActions;

    std::unordered_map<int, std::string> mKeyMap;
};