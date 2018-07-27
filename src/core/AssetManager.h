#pragma once
#include <unordered_map>
#include "Texture.h"
#include "Sound.h"

namespace Vulture2D {
    using std::unordered_map;

    class AssetManager {
    public:
        ~AssetManager();
        static AssetManager& getInstance();

        Texture* createTexture(string path, string name, SDL_Renderer*);
        Sound* createSound(string path, string name, bool loops);

        void registerTexture(Texture* texture, string name);
        void registerSound(Sound* sound, string name);
        Texture* getTexture(string name);
        Sound* getSound(string name);

    private:
        unordered_map<string, Texture*> textures;
        unordered_map<string, Sound*> sounds;

        static AssetManager* instance;

        AssetManager() {};
        AssetManager(AssetManager const&) {}
        AssetManager& operator=(AssetManager const& e) {};
    };
}