#include "Texture.h"

namespace Vulture2D {
    Texture::Texture(): mTexture(nullptr), mWidth(0), mHeight(0) {}
    Texture::Texture(string path, SDL_Renderer* renderer) {
        SDL_Surface* temp;
        temp = IMG_Load(path.c_str());
        if (!temp) {
            std::cout << "Couldn't load image" << std::endl;
        }
        else {
            mWidth = temp->w;
            mHeight = temp->h;

            mTexture = SDL_CreateTextureFromSurface(renderer, temp);
            SDL_FreeSurface(temp);
        }
    }

    Texture::~Texture() {
        if (mTexture) {
            SDL_DestroyTexture(mTexture);
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
}