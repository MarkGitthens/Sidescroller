#pragma once
#include <SDL.h>
#include <atomic>
#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include <thread>
#include "Entity.h"
#include "Renderable.h"
#include "TiledMap.h"
#include "Camera.h"
#include "Audio.h"
#include "AABBCollider.h"

using std::string;
using std::unordered_map;

class Scene {
public:
    Scene() : mSceneName("default") {};
    Scene(const string name) : mSceneName(name) {};
    Scene(const string name, SDL_Rect world) : mSceneName(name), mWorldSpace(world) {};
    Scene(const Scene& old) : mSceneName(old.mSceneName), mWorldSpace(old.mWorldSpace), mEntityMap(old.mEntityMap) {};
    ~Scene() {
        stopThreads();
        mBackgroundThread.join();
    };

    //Register a new entity for use in the scene
    void registerEntity(Entity* entity) {
        string name = entity->getName();

        mEntityMap[entity->getName()] = entity;
        Renderable* temp = dynamic_cast<Renderable*>(entity);
        if (temp) {
            mRenderMap[name] = temp;
			temp->setRenderId(mRenderMap.size());
        }

        AABBCollider* tempCollider = dynamic_cast<AABBCollider*>(entity);
        if (tempCollider) {
            mColliders[name] = (dynamic_cast<AABBCollider*>(entity));
        }
    }

    //Register an entity that should be tracked on a seperate thread
    void registerOffScreenEntity(Entity* entity) {
        if (entity != nullptr) {
            mOffScreenEntityMap[entity->getName()] = entity;
        }
    }

    void setName(std::string name) {
        mSceneName = name;
    }
    void setCamera(Camera* camera) {
        mCamera = camera;
    }

    void setTiledMap(TiledMap* tiledMap) {
        mTiledMap = tiledMap;
    }
    void removeEntity(char* name) {
        if (mEntityMap.find(name) != mEntityMap.end()) {
            mEntityMap.erase(name);
        }
        if (mRenderMap.find(name) != mRenderMap.end()) {
            mRenderMap.erase(name);
        }
        if (mColliders.find(name) != mColliders.end()) {
            mColliders.erase(name);
        }
    }
    Entity* getEntity(char* name) { return mEntityMap[name]; }
    std::string getName() { return mSceneName; }

    void updateScene() {
        for (std::pair<string, Entity*> e : mEntityMap) {
            e.second->update();
        }

        checkCollisions();
        mCamera->update();       
    }

    //Render all renderable entities in the scene.
    void renderScene() {
        SDL_RenderClear(Renderer::getInstance().getRenderer());

        mTiledMap->render(mCamera->getCameraRect());

        for (std::pair<string, Renderable*> r : mRenderMap) {
            r.second->render(mCamera->getCameraRect());
        }

        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }
    //Iterate through all registered colliders and if one is colliding with another add each other to their respective
    //collider list for further processing
    void checkCollisions() {
        for (auto start = mColliders.begin(); start != mColliders.end(); start++) {
            for (auto j = start; j != mColliders.end(); ++j) {
                if (start != j) {
                    if ((*start).second->colliding(*(*j).second)) {
                        (*start).second->addCollider((*j).second);
                        (*j).second->addCollider((*start).second);
                    }
                }
            }
            (*start).second->handleCollision("test", *(*start).second);
        }
    }

    // Init and start the background thread
    void initThreads() {
        mRunning = true;
        mBackgroundThread = std::move(std::thread(&Scene::updateOffScreen, this));
    }

    // Stop the background thread by setting mRunning to false
    void stopThreads() {
        mRunning = false;
    }

    // Thread function to run in the background to handle updating the off-screen entities
    void updateOffScreen() {
        while (mRunning) {
            for (std::pair<string, Entity*> e : mOffScreenEntityMap) {
                e.second->update();
            }
        }
    }

private:
    string mSceneName;
    SDL_Rect mWorldSpace;
    Camera* mCamera;

    TiledMap* mTiledMap;
    unordered_map<string, Renderable*> mRenderMap;
    unordered_map<string, Entity*> mEntityMap;

    unordered_map<string, AABBCollider*> mColliders;
    // seperate thread from render
    std::atomic<bool> mRunning;
    std::thread mBackgroundThread;
    unordered_map<string, Entity*> mOffScreenEntityMap;
};