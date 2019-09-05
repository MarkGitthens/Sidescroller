#include "AssetManager.h"

namespace Vulture2D {
    AssetManager* AssetManager::instance = nullptr;

    AssetManager::~AssetManager(){
        for(auto i : textures) {
            if(i.second)
                delete i.second;
        }
        textures.clear();
        
        for(auto chunk : sounds) {
            if(chunk.second)
                Mix_FreeChunk(chunk.second);
        }
        sounds.clear();
    }

    AssetManager& AssetManager::getInstance() {
        if(!instance) {
            instance = new AssetManager();
        }
        return *instance;
    }

    void AssetManager::destroy() {
        delete instance;
    }

    Texture* AssetManager::createTexture(string path, string name, SDL_Renderer* renderer) {
        Texture* texture = new Texture(path, renderer);

        if(textures.find(name) != textures.end()) {
            return textures.at(name);
        }
        textures.insert(std::pair<string, Texture*>(name, texture));
        return texture;
    }

    Mix_Chunk* AssetManager::createSound(string path, string name) {
        Mix_Chunk* chunk = Mix_LoadWAV(path.c_str());

        sounds.insert(std::pair<string, Mix_Chunk*>(name, chunk));
        return chunk;
    }

    void AssetManager::registerTexture(Texture* texture, string name) {
        textures.insert(std::pair<string, Texture*>(name, texture));
    }

    void AssetManager::registerSound(Mix_Chunk* sound, string name) {
        sounds.insert(std::pair<string, Mix_Chunk*>(name, sound));
    }

    Texture* AssetManager::getTexture(string name) {
        return textures[name];
    }

    Mix_Chunk* AssetManager::getSound(string name) {
        return sounds.find(name) == sounds.end() ? nullptr : sounds.at(name);
    }
}