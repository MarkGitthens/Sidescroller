#pragma once
#include "Renderable.h"

namespace Vulture2D {
    class AnimatedSprite : public Renderable {
    public:
        virtual void render(SDL_Rect*) = 0;

        void setFrameCount(int count) {
            frameCount = count;
        }

        void setFrameDelay(int delay) {
            frameDelay = delay;
        }

        void setFrameDimensions(int w, int h) {
            frameWidth = w;
            frameHeight = h;
        }
        void loops(bool loop) {
            this->loop = loop;
        }
        void isCyclic(bool cyclic) {
            this->cyclic = cyclic;
        }

    protected:
        Vector2D currentFramePosition;
        bool incrementing = true;
        int currentFrame=0;
        int frameCount;
        int frameDelay;
        int elapsedFrames = 0;
        bool cyclic;
        bool loop;
        int frameWidth, frameHeight;
    };
}