#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using std::string;
namespace Vulture2D {
    class Texture {
    public:
        Texture();
        ~Texture();
        Texture(SDL_Texture*);
        Texture(string);
        SDL_Texture* getTexture();
        const unsigned int getWidth();
        const unsigned int getHeight();
    private:
        unsigned int mWidth, mHeight;
        SDL_Texture* mTexture;
    };
}