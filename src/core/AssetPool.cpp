#include "AssetPool.h"

namespace Vulture2D {
    AssetPool* AssetPool::instance = nullptr;

    AssetPool::~AssetPool(){
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

    AssetPool& AssetPool::getInstance() {
        if(!instance) {
            instance = new AssetPool();
        }
        return *instance;
    }

    Texture* AssetPool::createTexture(string path, string name, SDL_Renderer* renderer) {
        Texture* texture = new Texture(path, renderer);

        if(textures.find(name) != textures.end()) {
            return textures.at(name);
        }
        textures.insert(std::pair<string, Texture*>(name, texture));
        return texture;
    }

    Sound* AssetPool::createSound(string path, string name) {
        Sound* sound = new Sound(path);

        if(sounds.find(name) != sounds.end()) {
            return sounds.at(name);
        }
        sounds.insert(std::pair<string, Sound*>(name, sound));
    }

    void AssetPool::registerTexture(Texture* texture, string name) {
        textures.insert(std::pair<string, Texture*>(name, texture));
    }

    void AssetPool::registerSound(Sound* sound, string name) {
        sounds.insert(std::pair<string, Sound*>(name, sound));
    }

    Texture* AssetPool::getTexture(string name) {
        return textures[name];
    }

    Sound* AssetPool::getSound(string name) {
        return sounds[name];
    }
}