#include "Texture.h"
#include <iostream>
#include "Renderer.h"
Texture::Texture() {
    mTexture = nullptr;
    mWidth = mHeight = 0;
}
Texture::~Texture() {
    mWidth = mHeight = 0;
    if (mTexture) {
        delete mTexture;
        mTexture = nullptr;
    }
}
Texture::Texture(SDL_Texture* texture) {
    mTexture = texture;
}
Texture::Texture(const char* path) {
    SDL_Surface* temp;
    temp = IMG_Load(path);
    if (!temp) {
        std::cout << "Couldn't load image" << std::endl;
    }
    else {
        mWidth = temp->w;
        mHeight = temp->h;

        mTexture = SDL_CreateTextureFromSurface(Renderer::getInstance().getRenderer(), temp);
        SDL_FreeSurface(temp);
    }

}

const unsigned int Texture::getWidth() {
    return mWidth;
}

const unsigned int Texture::getHeight() {
    return mHeight;
}

SDL_Texture* Texture::getTexture() {
    return mTexture;
}

