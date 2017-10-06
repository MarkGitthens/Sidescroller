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
    }
    void setSprite(Texture* texture) {
        if (mImage)
            delete mImage;
        mImage = texture;
    }

    void setLayer(int layers) { layer = layers; }
    int getLayer() { return layer; }

    Texture* getTexture() { return mImage; }
    SDL_Texture* getSDLTexture() { return mImage->getTexture(); }

    virtual void render(SDL_Rect*) = 0;

protected:
    int layer = 0;
    Texture* mImage;
};