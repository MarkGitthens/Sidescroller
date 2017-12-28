#pragma once
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"

class Renderable {
public:
    Renderable() : mImage(nullptr) {};
    ~Renderable() {
        if (mImage)
            delete mImage;
        mImage = nullptr;
    }

    void createFromPath(char* path) {
        mImage = new Texture(path);
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