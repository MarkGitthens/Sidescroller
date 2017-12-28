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
        Renderable* temp = dynamic_cast<Renderable*>(entity);
		if (mEntityMap.find(entity->getName()) != mEntityMap.end()) {
			mEntityMap.erase(mEntityMap.find(entity->getName()));
			//mRenderList.erase(mRenderList.begin() + temp->getRenderId());
		}
        mEntityMap[entity->getName()] = entity;
        if (temp) {
            mRenderList.push_back(temp);
			temp->setRenderId(mRenderList.size());
        }

        AABBCollider* tempCollider = dynamic_cast<AABBCollider*>(entity);
        if (tempCollider) {
            mColliders.push_back(dynamic_cast<AABBCollider*>(entity));
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

        for (Renderable* r : mRenderList) {
                r->render(mCamera->getCameraRect());
        }

        SDL_RenderPresent(Renderer::getInstance().getRenderer());
    }
    //Iterate through all registered colliders and if one is colliding with another add each other to their respective
    //collider list for further processing
    void checkCollisions() {
        for (auto start = mColliders.begin(); start != mColliders.end(); start++) {
            for (auto j = start + 1; j != mColliders.end(); j++) {
                if ((*start)->colliding(**j)) {
                    (*start)->addCollider(*j);
                    (*j)->addCollider(*start);
                }
            }
            (*start)->handleCollision("test", **start);
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
    std::vector<Renderable*> mRenderList;
    unordered_map<string, Entity*> mEntityMap;

    std::vector<AABBCollider*> mColliders;
    // seperate thread from render
    std::atomic<bool> mRunning;
    std::thread mBackgroundThread;
    unordered_map<string, Entity*> mOffScreenEntityMap;
};