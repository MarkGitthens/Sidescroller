#pragma once
#include "Entity.h"
#include "Texture.h"
#include "Renderable.h"

class Box : public Entity, public Renderable {
public:
    Box(): mTexture(nullptr) {};
    Box(Texture* texture) : mTexture(texture) {};
    ~Box();
    void update();
    void handleInput();
    void setImage(Texture* image);
    Texture* getImage();
    virtual void render(SDL_Rect*);
private:
    Texture* mTexture;
};