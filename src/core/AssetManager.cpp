#include "AssetManager.h"

namespace Vulture2D {
    AssetManager* AssetManager::instance = nullptr;

    AssetManager::~AssetManager(){
        for(auto i : textures) {
            if(i.second)
                delete i.second;
            textures.erase(i.first);
        }

        for(auto i : sounds) {
            if(i.second)
                delete i.second;
            sounds.erase(i.first);
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

    Sound* AssetManager::createSound(string path, string name) {
        Sound* sound = new Sound(path);

        if(sounds.find(name) != sounds.end()) {
            return sounds.at(name);
        }
        sounds.insert(std::pair<string, Sound*>(name, sound));
        return sound;
    }

    void AssetManager::registerTexture(Texture* texture, string name) {
        textures.insert(std::pair<string, Texture*>(name, texture));
    }

    void AssetManager::registerSound(Sound* sound, string name) {
        sounds.insert(std::pair<string, Sound*>(name, sound));
    }

    Texture* AssetManager::getTexture(string name) {
        return textures[name];
    }

    Sound* AssetManager::getSound(string name) {
        return sounds[name];
    }
}