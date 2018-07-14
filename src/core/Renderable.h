#pragma once
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"
#include <iostream>
namespace Vulture2D {
    class Renderable {
    public:
        Renderable() : mImage(nullptr) {};
        virtual ~Renderable() {
            std::cout << "Destroying renderable" << std::endl;
            if (mImage)
                delete mImage;
            mImage = nullptr;
        }

        void createFromPath(char* path, SDL_Renderer* renderer) {
            mImage = new Texture(path, renderer);
            mRect.w = mImage->getWidth();
            mRect.h = mImage->getHeight();
        }
        void setSprite(Texture* texture) {
            if (mImage)
                delete mImage;
            mImage = texture;
        }

        void setRenderId(int id) { mRenderId = id; }
        int getRenderId() { return mRenderId; }

        Texture* getTexture() { return mImage; }
        SDL_Texture* getSDLTexture() { return mImage->getTexture(); }

        SDL_Rect* getRenderRect() { return &mRect; }
        virtual void render(SDL_Rect*) = 0;

    protected:
        int mRenderId = 0;
        SDL_Rect mRect;
        Texture* mImage;
    };
}