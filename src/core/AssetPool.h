#include <unordered_map>
#include "Texture.h"
#include "Sound.h"

namespace Vulture2D {
    using std::unordered_map;

    class AssetPool {
    public:
        ~AssetPool();
        static AssetPool& getInstance();

        Texture* createTexture(string path, string name, SDL_Renderer*);
        Sound* createSound(string path, string name);

        void registerTexture(Texture* texture, string name);
        void registerSound(Sound* sound, string name);
        Texture* getTexture(string name);
        Sound* getSound(string name);

    private:
        unordered_map<string, Texture*> textures;
        unordered_map<string, Sound*> sounds;

        static AssetPool* instance;

        AssetPool() {};
        AssetPool(AssetPool const&) {}
        AssetPool& operator=(AssetPool const& e) {};
    };
}