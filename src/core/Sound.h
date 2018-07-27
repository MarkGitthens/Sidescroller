#pragma once
#include <SDL.h>
#include <string>
#include <iostream>

namespace Vulture2D {
    using std::string;
    class Sound {
    public:
        Sound() : soundLength(0), soundData(nullptr) {}
        Sound(string path) {
            loadFromFile(path);
        }
        ~Sound();

        SDL_AudioSpec* getAudioInformation();
        bool loadFromFile(string path);
        Uint32 getLength();
        void destroySound();

        Uint8* getSoundData();
        void setLoops(bool);
        bool loops();

    private:
        bool loop;
        SDL_AudioSpec soundInformation;
        Uint32 soundLength;
        Uint8* soundData;

    };
}