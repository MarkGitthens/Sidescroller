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
    Scene(const char* name) : mSceneName(name) {};
    Scene(const char* name, SDL_Rect world) : mSceneName(name), mWorldSpace(world) {};
    Scene(const Scene& old) : mSceneName(old.mSceneName), mWorldSpace(old.mWorldSpace), mEntityMap(old.mEntityMap) {};
    ~Scene() {
        stopThreads();
        mBackgroundThread.join();
    };

    void registerEntity(Entity* entity) { 
        Renderable* temp = dynamic_cast<Renderable*>(entity);
        mEntityMap[entity->getName()] = entity;
        if (temp) {
            if (mRenderList.size() <= temp->getLayer()) {
                mRenderList.resize(temp->getLayer() + 1);
            } 
            mRenderList.at(temp->getLayer()-1).emplace_back(temp);
        }

        AABBCollider* tempCollider = dynamic_cast<AABBCollider*>(entity);
        if (tempCollider) {
            mColliders.push_back(tempCollider);
        }
    }

    void registerOffScreenEntity(Entity* entity) {
        if (entity != nullptr) {
            mOffScreenEntityMap[entity->getName()] = entity;
        }
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
    }
    Entity* getEntity(char* name) { return mEntityMap[name]; }
    const char* getName() { return mSceneName.c_str(); }

    void updateScene() {
        for (std::pair<char*, Entity*> e : mEntityMap) {
            e.second->update();
        }

        checkCollisions();
        mCamera->update();

        SDL_RenderClear(Renderer::getInstance().getRenderer());

        mTiledMap->render(mCamera->getCameraRect());
        for (int i = 0; i < mRenderList.size(); i++) {
            for (Renderable* r : mRenderList.at(i)) {
                r->render(mCamera->getCameraRect());
            }
        }

        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }

    void checkCollisions() {

        //mColliders[0]->colliding(*mColliders[1]);

        for (auto start = mColliders.begin(); start != mColliders.end() - 1; start++) {
            for (auto j = start + 1; j != mColliders.end(); j++) {
                if ((*start)->colliding(**j)) {
                    Entity* tempStart = dynamic_cast<Entity*>(*start);
                    Entity* tempJ = dynamic_cast<Entity*>(*j);

                    (*start)->handleCollision(tempJ->getName(), **j);
                    (*j)->handleCollision(tempStart->getName(), **start);
                }
            }
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
            for (std::pair<char*, Entity*> e : mOffScreenEntityMap) {
                e.second->update();
            }
        }
    }

    void clearRenderList();
    void registerRenderable(Renderable*);

private:
    string mSceneName;
    SDL_Rect mWorldSpace;
    Camera* mCamera;

    TiledMap* mTiledMap;
    std::vector<std::vector<Renderable*>> mRenderList;
    unordered_map<char*, Entity*> mEntityMap;

    std::vector<AABBCollider*> mColliders;
    // seperate thread from render
    std::atomic<bool> mRunning;
    std::thread mBackgroundThread;
    unordered_map<char*, Entity*> mOffScreenEntityMap;
};