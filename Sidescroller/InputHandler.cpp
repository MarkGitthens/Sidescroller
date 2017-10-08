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
        std::string actionName = mKeyMap[mEvent.key.keysym.sym];
        if (mEvent.type == SDL_QUIT) {
            mTriggeredActions["SDL_QUIT"] = true;
        }
            //send message to close window
        if (mEvent.type == SDL_KEYDOWN) {
            mTriggeredActions[actionName] = true;
        }
        if (mEvent.type == SDL_KEYUP) {
            mTriggeredActions[actionName] = false;
            if (mPressedTriggeredActions[actionName] < 1)
                mPressedTriggeredActions[actionName] = mActions[actionName];
        }
    }
}

bool InputHandler::actionTriggered(std::string action) {
    if (mTriggeredActions.find(action) != mTriggeredActions.end())
        return mTriggeredActions[action];
    else
        return false;
}

bool InputHandler::actionPressTriggered(std::string action) {
    if (mPressedTriggeredActions.find(action) != mPressedTriggeredActions.end()) {
        int eventsLeftToTrigger = mPressedTriggeredActions[action];
        if (eventsLeftToTrigger > 0) {
            mPressedTriggeredActions[action] = eventsLeftToTrigger - 1;
            return true;
        }
    }
    return false;
}

void InputHandler::addKeyAction(int key, std::string tag) {
    mKeyMap.emplace(key, tag);
    if (mActions.find(tag) != mActions.end()) {
        mActions[tag] = mActions[tag] + 1;
    }
    else {
        mActions[tag] = 1;
        mPressedTriggeredActions[tag] = 0;
    }
}

void InputHandler::removeKeyAction(int key) {
    mKeyMap.erase(key);
}