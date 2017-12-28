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
        //This causes a crash
        mBackgroundThread.join();
    };

    void registerEntity(Entity* entity) {
        if (entity == nullptr) {
            return;
        }
        string name = entity->getName();

        mEntityMap[entity->getName()] = entity;
        Renderable* temp = dynamic_cast<Renderable*>(entity);
        if (temp) {
            mRenderMap[name] = temp;
			temp->setRenderId(mRenderMap.size());
        }

        AABBCollider* tempCollider = dynamic_cast<AABBCollider*>(entity);
        if (tempCollider) {
            if (tempCollider->isTrigger())
                mTriggers[name] = tempCollider;
            else
                mColliders[name] = tempCollider;
        }
    }

    //Register an entity that should be tracked on a seperate thread
    void registerOffScreenEntity(Entity* entity) {
        if (entity != nullptr) {
            mOffScreenEntityMap[entity->getName()] = entity;
        }
    }

    void removeEntity(string name) {
        if (mTriggers.find(name) != mTriggers.end()) {
            mTriggers.erase(name);
        }
        if (mColliders.find(name) != mColliders.end()) {
            mColliders.erase(name);
        }
        if (mRenderMap.find(name) != mRenderMap.end()) {
            mRenderMap.erase(name);
        }
        if (mEntityMap.find(name) != mEntityMap.end()) {
            delete mEntityMap.find(name)->second;
            mEntityMap.find(name)->second = nullptr;
            mEntityMap.erase(name);
        }
    }

    void updateScene() {
        for (std::pair<string, Entity*> e : mEntityMap) {
            if (e.second == nullptr)
                continue;
             e.second->update();
        }

        checkCollisions();
        mCamera->update();
    }

    // Thread function to run in the background to handle updating the off-screen entities
    void updateOffScreen() {
        while (mRunning) {
            for (std::pair<string, Entity*> e : mOffScreenEntityMap) {
                if (e.second == nullptr)
                    continue;
                e.second->update();
            }
        }
    }

    void renderScene() {
        SDL_RenderClear(Renderer::getInstance().getRenderer());

        mTiledMap->render(mCamera->getCameraRect());

        for (std::pair<string, Renderable*> r : mRenderMap) {
            if (r.second == nullptr)
                continue;
            r.second->render(mCamera->getCameraRect());
        }

        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }

    //Checks for "physical" collisions, then collisions against triggers.
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
            (*start).second->handleCollisions();

            for (auto j = mTriggers.begin(); j != mTriggers.end(); j++) {
                if ((*start).second->colliding(*(*j).second))
                    (*start).second->handleTrigger(dynamic_cast<Entity*>((*j).second)->getName());
            }
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

    Entity* getEntity(char* name) { 
        return mEntityMap[name];
    }
    
    std::string getName() { 
        return mSceneName; 
    }

    // Init and start the background thread
    void initThreads() {
        mRunning = true;
        mBackgroundThread = std::move(std::thread(&Scene::updateOffScreen, this));
    }

    void stopThreads() {
        mRunning = false;
    }


private:
    string mSceneName;
    SDL_Rect mWorldSpace;
    Camera* mCamera;

    TiledMap* mTiledMap;
    unordered_map<string, Renderable*> mRenderMap;
    unordered_map<string, Entity*> mEntityMap;

    unordered_map<string, AABBCollider*> mColliders;
    unordered_map<string, AABBCollider*> mTriggers;

    std::atomic<bool> mRunning;
    std::thread mBackgroundThread;

    unordered_map<string, Entity*> mOffScreenEntityMap;
};