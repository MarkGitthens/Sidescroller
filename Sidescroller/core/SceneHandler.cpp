#include "SceneHandler.h"

SceneHandler* SceneHandler::instance = nullptr;
void SceneHandler::changeScene(Scene* newScene) {
    mCurrentScene = newScene;
}

void SceneHandler::changeScene(string sceneName) {
    mCurrentScene = (mRegisteredScenes.find(sceneName) != mRegisteredScenes.end()) ? mRegisteredScenes.at(sceneName) : nullptr;
}

void SceneHandler::registerScene(Scene* scene) {
    mRegisteredScenes[scene->getName()] = scene;
    if (mCurrentScene == nullptr) {
        mCurrentScene = scene;
    }
}

void SceneHandler::removeScene(string name) {
    mRegisteredScenes.erase(name);
}

Scene* SceneHandler::getCurrentScene() {
    return mCurrentScene;
}

SceneHandler& SceneHandler::getInstance() {
    if (!instance) {
        instance = new SceneHandler();
    }
    return *instance;
}