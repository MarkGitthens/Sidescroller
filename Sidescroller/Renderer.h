#pragma once
#include <vector>
#include <SDL.h>
#include "Texture.h"

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
    void drawTexture(Texture*, SDL_Rect*, SDL_Rect*);
    void setClearColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    SDL_Renderer* getRenderer();

private:
    static Renderer* instance;

    Renderer(Renderer const&) {}
    Renderer& operator=(Renderer const& e) {}
    //TODO: Possible memory leak
    ~Renderer() { 
        if (instance) { 
            delete instance; 
        }
        instance = nullptr; 
    }
    SDL_Renderer* mRenderer;
};