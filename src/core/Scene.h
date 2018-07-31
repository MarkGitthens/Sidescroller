#pragma once
#include <SDL.h>
#include <string>
#include <queue>
#include <unordered_map>
#include <iostream>
#include "EventHandler.h"
#include "Entity.h"
#include "Renderable.h"
#include "../entities/TiledMap.h"
#include "../entities/Camera.h"
#include "../physics/AABBCollider.h"

using std::string;
using std::unordered_map;

namespace Vulture2D {
    class Scene : public EventHandler{
    public:
        Scene() : mSceneName("default"), mWorldSpace(), sceneWidth(0), sceneHeight(0) {};
        Scene(const string name) : mSceneName(name), mWorldSpace(), sceneWidth(0), sceneHeight(0) {};
        Scene(const string name, SDL_Rect world) : mSceneName(name), mWorldSpace(world), sceneWidth(0), sceneHeight(0) {};
        ~Scene() {};

        void registerEntity(Entity* entity) {
            if (entity == nullptr) {
                return;
            }

            int currentEntity = entity->getID();
            
            string name = entity->getName();

            if (mEntityMap.find(currentEntity) != mEntityMap.end()) {
                removeEntity(currentEntity);
            }

            mEntityMap[currentEntity] = entity;
            Renderable* temp = dynamic_cast<Renderable*>(entity);
            if (temp) {
                mRenderMap[currentEntity] = temp;
                temp->setRenderId(mRenderMap.size());
            }

            AABBCollider* tempCollider = dynamic_cast<AABBCollider*>(entity);
            if (tempCollider) {
                if (tempCollider->isTrigger())
                    mTriggers[currentEntity] = tempCollider;
                else
                    mColliders[currentEntity] = tempCollider;
            }
        }

        void deleteEntity(int id) {
            if (mEntityMap.find(id) != mEntityMap.end()) {
                mDeletedEntities.emplace_back(id);
            }
        }

        void updateScene() {
            for (std::pair<int, Entity*> e : mEntityMap) {
                e.second->update();
            }

            auto deleteIterator = mDeletedEntities.begin();
            while (deleteIterator != mDeletedEntities.end()) {
                removeEntity(*deleteIterator);
                deleteIterator = mDeletedEntities.erase(deleteIterator);
            }

            if(mCamera)
                mCamera->update();
        }

        void renderScene() {
            SDL_RenderClear(Renderer::getInstance().getRenderer());

            if(mCamera) {
                mTiledMap->render(mCamera->getCameraRect());
            } else {
                SDL_Rect rect;
                rect.x = 0;
                rect.y = 0;
                rect.w = 1280;
                rect.h = 720;
                mTiledMap->render(&rect);
            }
            

            for (std::pair<int, Renderable*> r : mRenderMap) {
                if (r.second == nullptr)
                    continue;
                if(mCamera) {
                    r.second->render(mCamera->getCameraRect());
                } else {
                    SDL_Rect rect;
                    rect.x = 0;
                    rect.y = 0;
                    rect.w = 1280;
                    rect.h = 720;
                    r.second->render(&rect);
                }
            }

            SDL_RenderPresent(Renderer::getInstance().getRenderer());
        }

        vector<AABBCollider*> checkCollisions(AABBCollider* collider) {
            vector<AABBCollider*> colliders;
            for(auto check = mColliders.begin(); check != mColliders.end(); check++) {
                if(collider == (check)->second)
                    continue;
                if(collider->colliding(*(*check).second)) {
                    colliders.push_back(check->second);
                }
            }

            for(auto check = mTriggers.begin(); check != mTriggers.end(); check++) {
                if(collider == (check)->second)
                    continue;
                if(collider->colliding(*(*check).second)) {
                    colliders.push_back(check->second);
                }
            }

            return colliders;
        }

        void setName(const std::string& name) {
            mSceneName = name;
        }

        void setSceneWidth(int width) {
            sceneWidth = width;
        }

        void setSceneHeight(int height) {
            sceneHeight = height;
        }
        void setCamera(Camera* camera) {
            delete mCamera;
            mCamera = camera;
        }

        void setTiledMap(TiledMap* tiledMap) {
            mTiledMap = tiledMap;
            sceneWidth = tiledMap->getWidth();
            sceneHeight = tiledMap->getHeight();
        }

        Entity* getEntity(int id) {
            return mEntityMap[id];
        }

        std::string getName() {
            return mSceneName;
        }
        
        TiledMap* getTiledMap() {
            return mTiledMap;
        }

        void destroy() {
            delete mCamera;
            delete mTiledMap;
        }

        int getSceneWidth() {
            return sceneWidth;
        }

        int getSceneHeight() {
            return sceneHeight;
        }

    private:
        string mSceneName;
        SDL_Rect mWorldSpace;
        Camera* mCamera = nullptr;

        TiledMap* mTiledMap = nullptr;

        int sceneWidth;
        int sceneHeight;

        unordered_map<int, Renderable*> mRenderMap;
        unordered_map<int, Entity*> mEntityMap;
        unordered_map<int, AABBCollider*> mColliders;
        unordered_map<int, AABBCollider*> mTriggers;

        std::vector<int> mDeletedEntities;

        unordered_map<int, Entity*> mOffScreenEntityMap;

        void removeEntity(int id) {
            if (mTriggers.find(id) != mTriggers.end()) {
                mTriggers.erase(id);
            }
            if (mColliders.find(id) != mColliders.end()) {
                mColliders.erase(id);
            }
            if (mRenderMap.find(id) != mRenderMap.end()) {
                mRenderMap.erase(id);
            }
            if (mEntityMap.find(id) != mEntityMap.end()) {
                delete mEntityMap.find(id)->second;
                mEntityMap.find(id)->second = nullptr;
                mEntityMap.erase(id);
            }
        }
    };
}
