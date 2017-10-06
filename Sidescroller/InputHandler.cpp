#include "InputHandler.h"

#include <iostream>
InputHandler* InputHandler::instance = nullptr;

InputHandler& InputHandler::getInstance() {
    if (!instance) {
        instance = new InputHandler();
    }
    return *instance;
}

void InputHandler::handleInput() {
    while (SDL_PollEvent(&mEvent) != 0) {
        if (mEvent.type == SDL_QUIT) {
            mTriggeredActions["SDL_QUIT"] = true;
        }
            //send message to close window
        if (mEvent.type == SDL_KEYDOWN) {
            std::string actionName = mKeyMap[mEvent.key.keysym.sym];
            mTriggeredActions[actionName] = true;
            
        }
        if (mEvent.type == SDL_KEYUP) {
            mTriggeredActions[mKeyMap[mEvent.key.keysym.sym]] = false;;
        }
    }
}

bool InputHandler::actionTriggered(std::string action) {
    return mTriggeredActions[action];
}

void InputHandler::addKeyAction(int key, std::string tag) {
    mKeyMap.emplace(key, tag);
}

void InputHandler::removeKeyAction(int key) {
    mKeyMap.erase(key);
}