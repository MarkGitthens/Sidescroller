#include "AssetManager.h"

namespace Vulture2D {
    AssetManager* AssetManager::instance = nullptr;

    AssetManager::~AssetManager(){
        for(auto i : textures) {
            if(i.second)
                delete i.second;
            textures.erase(i.first);
        }

        if(instance) {
            delete instance;
        }
        instance = nullptr;
    }

    AssetManager& AssetManager::getInstance() {
        if(!instance) {
            instance = new AssetManager();
        }
        return *instance;
    }

    Texture* AssetManager::createTexture(string path, string name, SDL_Renderer* renderer) {
        Texture* texture = new Texture(path, renderer);

        if(textures.find(name) != textures.end()) {
            return textures.at(name);
        }
        textures.insert(std::pair<string, Texture*>(name, texture));
        return texture;
    }

    Sound* createSound(string path, string name) {
        return nullptr;
    }

    void AssetManager::registerTexture(Texture* texture, string name) {
        textures.insert(std::pair<string, Texture*>(name, texture));
    }

    void registerSound(Mix_Chunk* sound, string name) {

    }

    Texture* AssetManager::getTexture(string name) {
        return textures[name];
    }

    Mix_Chunk* getSound(string name) {
        return nullptr;
    }
}