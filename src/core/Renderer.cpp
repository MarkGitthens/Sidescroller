#include "Renderer.h"

namespace Vulture2D {

    Renderer* Renderer::instance = nullptr;

    Renderer::Renderer() {
        mRenderer = nullptr;
    }

    Renderer::Renderer(SDL_Window* window, Uint32 flags) {
        createFromWindow(window, flags);
    }

    void Renderer::init(SDL_Window* window, Uint32 flags) {
        createFromWindow(window, flags);
    }

    void Renderer::destroy() {
        if (mRenderer)
            SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }

    Renderer& Renderer::getInstance() {
        if (!instance)
            instance = new Renderer();
        return *instance;
    }

    void Renderer::createFromWindow(SDL_Window* window, Uint32 flags) {
        //TODO: Need to do error checking.
        mRenderer = SDL_CreateRenderer(window, -1, flags);
    }

    void Renderer::drawTexture(Texture* texture, int x, int y, int w, int h) {
        SDL_Rect* dest = new SDL_Rect;

        dest->x = x;
        dest->y = y;
        dest->w = w;
        dest->h = h;

        SDL_RenderCopy(mRenderer, texture->getTexture(), NULL, dest);
    }

    void Renderer::drawTexture(Texture* texture, SDL_Rect* dest) {
        SDL_RenderCopy(mRenderer, texture->getTexture(), NULL, dest);
    }

    void Renderer::drawTexture(Texture* texture, SDL_Rect* src, SDL_Rect* dest, const double angle, const SDL_Point* center, const SDL_RendererFlip flip) {
        SDL_RenderCopyEx(mRenderer, texture->getTexture(), src, dest, angle, center, flip);
    }

    void Renderer::setClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
        SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
    }

    SDL_Renderer* Renderer::getRenderer() {
        return mRenderer;
    }
}
