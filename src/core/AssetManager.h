#pragma once
#include <unordered_map>
#include "Texture.h"

namespace Vulture2D {
    using std::unordered_map;

    class AssetManager {
    public:
        ~AssetManager();
        static AssetManager& getInstance();

        Texture* createTexture(string path, string name, SDL_Renderer*);
        void registerTexture(Texture* texture, string name);
        Texture* getTexture(string name);

    private:
        unordered_map<string, Texture*> textures;

        static AssetManager* instance;

        AssetManager() {};
        AssetManager(AssetManager const&) {}
        AssetManager& operator=(AssetManager const& e) {};
    };
}