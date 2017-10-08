#include "Box.h"

Box::~Box() {
    if (mTexture) {
        delete mTexture;
    }
    mTexture = nullptr;
}
void Box::update() {

}

void Box::handleInput() {

}

void Box::render(SDL_Rect* camera) {
    //Renderer::getInstance().drawTexture(getTexture(), getRect());
}
void Box::setImage(Texture* texture) {
    mTexture = texture;
}

Texture* Box::getImage() {
    return mTexture;
}