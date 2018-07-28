#include "InputHandler.h"

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
                }
            }
        }
    }

    bool InputHandler::actionTriggered(const std::string& action) {
        return mPressedKeys[mActionMap[action]];
    }

    bool InputHandler::actionHeld(const std::string& action) {
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

    vector<int> InputHandler::getPressedKeys() {
        vector<int> temp;

        for (auto k : mPressedKeys) {
            if (k.second)
                temp.push_back(k.first);
        }
        return temp;
    }

    vector<int> InputHandler::getHeldKeys() {
        vector<int> temp;

        for (auto k : mHeldKeys) {
            if (k.second)
                temp.push_back(k.first);
        }
        return temp;
    }

    vector<int> InputHandler::getReleasedKeys() {
        vector<int> temp;

        for (auto k : mReleasedKeys) {
            if (k.second)
                temp.push_back(k.first);
        }
        return temp;
    }
}