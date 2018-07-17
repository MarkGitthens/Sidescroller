#pragma once
#include "Animation.h"
#include "Renderable.h"

namespace Vulture2D {
    class AnimatedSprite : public Renderable {
    public:
        virtual void render(SDL_Rect*) = 0;

        void registerAnimation(Animation animation) {
            animations.insert(std::pair<string, Animation>(animation.getName(), animation));
        }

        void setAnimation(string name) {
            currentAnimation = name;
        }

        void removeAnimation(string name) {
            animations.erase(name);
        }

    protected:
        string currentAnimation;
        std::unordered_map<string, Animation> animations;
    };
}