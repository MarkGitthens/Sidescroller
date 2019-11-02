#include "SceneHandler.h"

SceneHandler* SceneHandler::instance = nullptr;
void SceneHandler::changeScene(Scene* newScene) {
  mCurrentScene = newScene;
  mCurrentScene->startScene();
}

void SceneHandler::changeScene(string sceneName) {
  if (mRegisteredScenes.find(sceneName) != mRegisteredScenes.end()) {
    if (mCurrentScene) {
      if (mCurrentScene->getName() != sceneName) {
        mCurrentScene->stopScene();
        mCurrentScene = mRegisteredScenes.at(sceneName);
        mCurrentScene->startScene();
      }
    } else {
      mCurrentScene = mRegisteredScenes.at(sceneName);
      mCurrentScene->startScene();
    }
  }
}

void SceneHandler::registerScene(Scene* scene) {
  mRegisteredScenes[scene->getName()] = scene;
}

void SceneHandler::removeScene(string name) { mRegisteredScenes.erase(name); }

Scene* SceneHandler::getCurrentScene() { return mCurrentScene; }

SceneHandler& SceneHandler::getInstance() {
  if (!instance) {
    instance = new SceneHandler();
  }
  return *instance;
}

void SceneHandler::destroy() {
  if (instance) delete instance;
}