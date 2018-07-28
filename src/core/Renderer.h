#pragma once
#include <vector>
#include <SDL.h>
#include "Texture.h"

namespace Vulture2D {
    class Renderer {
    public:

        static Renderer& getInstance();

        Renderer();
        Renderer(SDL_Window*, Uint32);

        void init(SDL_Window*, Uint32);
        void destroy();

        void createFromWindow(SDL_Window*, Uint32);
        void drawTexture(Texture*, int x, int y, int w, int h);
        void drawTexture(Texture*, SDL_Rect*);
        void drawTexture(Texture*, SDL_Rect*, SDL_Rect*, const double angle = 0, const SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
        void setClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

        SDL_Renderer* getRenderer();

    private:
        static Renderer* instance;

        ~Renderer() {
            if (instance) {
                delete instance;
            }
            instance = nullptr;
        }
        SDL_Renderer* mRenderer;
    };
}
