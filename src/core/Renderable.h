#pragma once
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"
#include <iostream>
namespace Vulture2D {
    class Renderable {
    public:
        Renderable() : image(nullptr) {};
        virtual ~Renderable() {
            std::cout << "Destroying renderable" << std::endl;
            if (image)
                delete image;
            image = nullptr;
        }

        void createFromPath(const char* path, SDL_Renderer* renderer) {
            image = new Texture(path, renderer);
        }
        void setSprite(Texture* texture) {
            if (image)
                delete image;
            image = texture;
        }

        void setRenderId(int id) { renderId = id; }
        int getRenderId() { return renderId; }

        Texture* getTexture() { return image; }
        SDL_Texture* getSDLTexture() { return image->getTexture(); }

        virtual void render(SDL_Rect*) = 0;

    protected:
        int renderId = 0;
        Texture* image;
    };
}
