#pragma once
#include <iostream>
#include <string>
#include <unordered_map>

#include "Scene.h"

using std::string;
using std::unordered_map;

namespace Vulture2D {
class SceneHandler {
 public:
  void changeScene(Scene*);
  void changeScene(string);
  // Register a new scene for later use. If there is no current scene then
  // assign the current scene to the newly registered scene.
  void registerScene(Scene*);

  void removeScene(string);

  Scene* getCurrentScene();
  static SceneHandler& getInstance();
  static void destroyInstance();

 private:
  ~SceneHandler() {
    auto deleteMap = mRegisteredScenes.begin();
    while (deleteMap != mRegisteredScenes.end()) {
      deleteMap->second->destroy();
      deleteMap = mRegisteredScenes.erase(deleteMap);
    }
    instance = nullptr;
  }
  SceneHandler(){};
  SceneHandler(const SceneHandler&) = delete;
  SceneHandler& operator=(const SceneHandler&) = delete;
  static SceneHandler* instance;

  Scene* mCurrentScene = nullptr;
  unordered_map<string, Scene*> mRegisteredScenes;
};
}  // namespace Vulture2D