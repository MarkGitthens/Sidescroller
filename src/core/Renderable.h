#pragma once
#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"
#include <iostream>
namespace Vulture2D {
    class Renderable {
    public:
        Renderable() : image(nullptr), visible(true), renderId(0) {};
        virtual ~Renderable() {}

        void createFromPath(const char* path, SDL_Renderer* renderer) {
            image = new Texture(path, renderer);
        }
        void setSprite(Texture* texture) {
            delete image;
            image = texture;
        }

        void setRenderId(int id) { renderId = id; }
        int getRenderId() { return renderId; }

        Texture* getTexture() { return image; }
        SDL_Texture* getSDLTexture() { return image->getTexture(); }

        virtual void render(SDL_Rect*) = 0;

        bool visibile() {
            return visible;
        }
        void setVisible(bool visible) {
            this->visible = visible;
        };

    protected:
        bool visible;
        int renderId;
        Texture* image;
    };
}
