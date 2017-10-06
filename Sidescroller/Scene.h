#pragma once
#include <SDL.h>
#include <string>
#include <queue>
#include <unordered_map>
#include "Entity.h"
#include "Renderable.h"
#include "CollisionHandler.h"
#include "TiledMap.h"
#include "Camera.h"

#include <iostream>
using std::string;
using std::unordered_map;


class Scene {
public:
    Scene() : mSceneName("default") {};
    Scene(const char* name) : mSceneName(name) {};
    Scene(const char* name, SDL_Rect world) : mSceneName(name), mWorldSpace(world) {};
    Scene(const Scene& old) : mSceneName(old.mSceneName), mWorldSpace(old.mWorldSpace), mEntityMap(old.mEntityMap) {};

    void registerEntity(Entity* entity) { 
        mEntityMap[entity->getName()] = entity; 
        Renderable* temp = dynamic_cast<Renderable*>(entity);
        if (temp) {
            if (mRenderList.size() <= temp->getLayer()) {
                mRenderList.resize(temp->getLayer() + 1);
            } 
            mRenderList.at(temp->getLayer()-1).emplace_back(temp);
        }
           

        Collidable* tempCollide = dynamic_cast<Collidable*>(entity);
        if (tempCollide) {
            std::cout << "registered collider" << std::endl;
            mCollisionHandler.registerCollider(tempCollide);
        }
    }

    void setCamera(Camera* camera) {
        mCamera = camera;
    }

    void setTiledMap(TiledMap* tiledMap) {
        mTiledMap = tiledMap;
    }
    void removeEntity(char* name) { mEntityMap.erase(name); }
    Entity* getEntity(char* name) { return mEntityMap[name]; }
    const char* getName() { return mSceneName.c_str(); }
    
    void updateScene() {
        for (std::pair<char*, Entity*> e : mEntityMap) {
            e.second->update();
        }
        mCollisionHandler.checkCollisions();

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

    void clearRenderList();
    void registerRenderable(Renderable*);

private:
    string mSceneName;
    SDL_Rect mWorldSpace;
    Camera* mCamera;

    TiledMap* mTiledMap;
    std::vector<std::vector<Renderable*>> mRenderList;
    unordered_map<char*, Entity*> mEntityMap;
    CollisionHandler mCollisionHandler;
};