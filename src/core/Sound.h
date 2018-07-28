#pragma once
#include <SDL_mixer.h>
#include "../util/Vector2D.h"

namespace Vulture2D {
    class Sound {
    public:
        Sound(const char* path, bool loops = false, int numLoops = 0, Vector2D* parent = nullptr): doesLoop(loops), numLoops(numLoops), parentPosition(parent), channel(-1) {
            chunk = Mix_LoadWAV(path);
        }

        bool loops();
        int loopCount();
        Mix_Chunk* getChunkData();
        const Vector2D getPosition();

        void setChannel(int);
        int getChannel();

    private:
        int channel;
        Vector2D* parentPosition;
        bool doesLoop;
        int numLoops;
        Mix_Chunk* chunk;
    };
}