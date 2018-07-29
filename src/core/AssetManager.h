#pragma once
#include <unordered_map>
#include <SDL_mixer.h>
#include "Texture.h"

namespace Vulture2D {
    using std::unordered_map;

    class AssetManager {
    public:
        
        static AssetManager& getInstance();

        Texture* createTexture(string path, string name, SDL_Renderer*);
        Mix_Chunk* createSound(string path, string name);
        void registerTexture(Texture* texture, string name);
        void registerSound(Mix_Chunk* sound, string name);
        Texture* getTexture(string name);
        Mix_Chunk* getSound(string name);


    private:
        unordered_map<string, Texture*> textures;
        unordered_map<string, Mix_Chunk*> sounds;

        static AssetManager* instance;

        AssetManager(const AssetManager&);
        AssetManager& operator=(const AssetManager&);
#pragma warning(suppress: 26439)
        AssetManager() {};
        ~AssetManager();
    };
}