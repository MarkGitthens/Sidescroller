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
#include "../entities/TiledMap.h"
#include "../entities/Camera.h"
#include "../physics/AABBCollider.h"

using std::string;
using std::unordered_map;

namespace Vulture2D {
    class Scene {
    public:
        Scene() : mSceneName("default") {};
        Scene(const string name) : mSceneName(name) {};
        Scene(const string name, SDL_Rect world) : mSceneName(name), mWorldSpace(world) {};
        Scene(const Scene& old) : mSceneName(old.mSceneName), mWorldSpace(old.mWorldSpace), mEntityMap(old.mEntityMap) {};
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

        //Register an entity that should be tracked on a seperate thread
        void registerOffScreenEntity(Entity* entity) {
            if (entity != nullptr) {
                mOffScreenEntityMap[entity->getID()] = entity;
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

            checkCollisions();

            auto deleteIterator = mDeletedEntities.begin();
            while (deleteIterator != mDeletedEntities.end()) {
                removeEntity(*deleteIterator);
                deleteIterator = mDeletedEntities.erase(deleteIterator);
            }

            mCamera->update();
        }

        void renderScene() {
            SDL_RenderClear(Renderer::getInstance().getRenderer());

            mTiledMap->render(mCamera->getCameraRect());

            for (std::pair<int, Renderable*> r : mRenderMap) {
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
                    if ((*start).second->colliding(*(*j).second)) {
                        (*start).second->handleTrigger(dynamic_cast<Entity*>((*j).second)->getName());
                        (*j).second->addCollider((*start).second);
                    }
                }
            }
        }

        bool checkCollisions(AABBCollider* collider) {
            for (auto check = mColliders.begin(); check != mColliders.end(); check++) {
                if (collider->colliding(*(*check).second)) {
                    return true;
                }
            }
            return false;
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

        Entity* getEntity(int id) {
            return mEntityMap[id];
        }

        std::string getName() {
            return mSceneName;
        }

        void destroy() {
            delete mCamera;
            delete mTiledMap;
        }


    private:
        string mSceneName;
        SDL_Rect mWorldSpace;
        Camera* mCamera;

        TiledMap* mTiledMap;

        //TODO: Need to assign entities valid Unique ID's so that I can do all references to the entity with those instead of the string names.
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
