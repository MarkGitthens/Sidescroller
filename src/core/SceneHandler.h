#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

namespace Vulture2D {
    class SceneHandler {
    public:
        void changeScene(Scene*);
        void changeScene(string);
        //Register a new scene for later use. If there is no current scene then assign the current scene to the newly registered scene.
        void registerScene(Scene*);

        void removeScene(string);

        Scene* getCurrentScene();
        static SceneHandler& getInstance();

    private:
        ~SceneHandler() {
            auto deleteMap = mRegisteredScenes.begin();

            while (deleteMap != mRegisteredScenes.end()) {
                delete deleteMap->second;
                deleteMap = mRegisteredScenes.erase(deleteMap);
            }

            delete instance;
            instance = nullptr;
        }
        SceneHandler() {};
        SceneHandler(const SceneHandler&) = delete;
        SceneHandler& operator=(const SceneHandler&) = delete;
        static SceneHandler* instance;

        Scene* mCurrentScene = nullptr;
        unordered_map<string, Scene*> mRegisteredScenes;
    };
}