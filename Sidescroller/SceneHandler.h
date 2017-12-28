#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
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
        if (instance) { 
            delete instance;
        } 
        instance = nullptr;
    }
    SceneHandler() {};
    SceneHandler(SceneHandler const&) {};
    SceneHandler& operator=(SceneHandler const& e) {};

    static SceneHandler* instance;

    Scene* mCurrentScene = nullptr;
    unordered_map<string, Scene*> mRegisteredScenes;
};