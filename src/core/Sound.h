#pragma once
#include <SDL_mixer.h>

namespace Vulture2D {
    class Sound {
    public:
        Sound(const char* path, bool loops = false, int numLoops = 0): loops(loops), loopCount(numLoops) {
            Mix_LoadMUS(path);
        }


    private:
        bool loops;
        int loopCount;
        Mix_Music* music;
    };
}