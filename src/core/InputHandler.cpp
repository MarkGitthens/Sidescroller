#include "InputHandler.h"
#include <iostream>
#include "KeyboardEvent.h"
#include "SceneHandler.h"

namespace Vulture2D {
    InputHandler* InputHandler::instance = nullptr;

    InputHandler& InputHandler::getInstance() {
        if (!instance) {
            instance = new InputHandler();
        }
        return *instance;
    }

    void InputHandler::handleInput() {

        mPressedKeys.clear();
        mReleasedKeys.clear();

        while (SDL_PollEvent(&mEvent) != 0) {
            if (mEvent.type == SDL_KEYDOWN || mEvent.type == SDL_KEYUP) {
                int key = mEvent.key.keysym.sym;
                std::string actionName = mKeyMap[key];

                if (!mHeldKeys[key]) {
                    SceneHandler::getInstance().getCurrentScene()->dispatchEvent(&KeyboardEvent(KeyboardEvent::KeyPress, key));
                }
                if (mEvent.type == SDL_QUIT) {
                    mHeldKeys[mActionMap["quit_game"]] = true;
                }
                if (mEvent.type == SDL_KEYDOWN) {
                    if (!mHeldKeys[key]) {
                        mPressedKeys[key] = true;
                        mHeldKeys[key] = true;
                    }
                }
                if (mEvent.type == SDL_KEYUP) {
                    mPressedKeys[key] = false;
                    mHeldKeys[key] = false;
                    mReleasedKeys[key] = true;
                    SceneHandler::getInstance().getCurrentScene()->dispatchEvent(&KeyboardEvent(KeyboardEvent::KeyReleased, key));
                }
            }
        }

        for (auto k : mHeldKeys) {
            if(k.second)
                SceneHandler::getInstance().getCurrentScene()->dispatchEvent(&KeyboardEvent(KeyboardEvent::KeyHeld, k.first));
        }
    }

    bool InputHandler::actionTriggered(std::string action) {
        return mPressedKeys[mActionMap[action]];
    }

    bool InputHandler::actionHeld(std::string action) {
        return mHeldKeys[mActionMap[action]];
    }

    void InputHandler::addKeyAction(int key, std::string tag) {
        mKeyMap.emplace(key, tag);
        mActionMap.emplace(tag, key);
    }

    void InputHandler::removeKeyAction(int key) {
        mActionMap.erase(mKeyMap[key]);
        mKeyMap.erase(key);
    }

    bool InputHandler::keyPressed(int key) {
        return mPressedKeys[key];
    }

    bool InputHandler::keyHeld(int key) {
        return mHeldKeys[key];
    }

    bool InputHandler::keyReleased(int key) {
        return mReleasedKeys[key];
    }
}