#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

using std::string;
class Texture{
public:
    Texture();
    ~Texture();
    Texture(SDL_Texture*);
    Texture(const char*);
    SDL_Texture* getTexture();
    const unsigned int getWidth();
    const unsigned int getHeight();
private:
    unsigned int mWidth, mHeight;
    SDL_Texture* mTexture;
};