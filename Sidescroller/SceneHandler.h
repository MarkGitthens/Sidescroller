#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;
class SceneHandler {
public:    
    //change the current scene to the provided scene
    void changeScene(Scene*);
    //Change the current scene to the registered scene identified by its name
    void changeScene(string);
    //Register a new scene for later use. If there is no current scene then assign the current scene to the newly registered scene.
    void registerScene(Scene*);
    
    //Remove a registered scene identified by it's name
    void removeScene(string);

    //Get the current scene
    Scene* getCurrentScene();
    static SceneHandler& getInstance();

private:
    ~SceneHandler();
    SceneHandler() {};
    SceneHandler(SceneHandler const&) {};
    SceneHandler& operator=(SceneHandler const& e) {};

    static SceneHandler* instance;

    Scene* mCurrentScene = nullptr;
    unordered_map<string, Scene*> mRegisteredScenes;
};