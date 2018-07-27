#include "Sound.h"

namespace Vulture2D {

    Sound::~Sound() {
        destroySound();
    }
    SDL_AudioSpec* Sound::getAudioInformation() {
        return &soundInformation;
    }

    bool Sound::loadFromFile(string path) {
        bool loaded = true;
        if(SDL_LoadWAV(path.c_str(), &soundInformation, &soundData, &soundLength) == NULL)
            loaded = false;

        soundInformation.callback = NULL;
        soundInformation.userdata = NULL;
        return  loaded;
    }

    Uint8* Sound::getSoundData() {
        return soundData;
    }
    
    Uint32 Sound::getLength() {
        return soundLength;
    }

    void Sound::setLoops(bool loop) {
        this->loop = loop;
    }

    bool Sound::loops() {
        return loop;
    }

    void Sound::destroySound() {
        SDL_FreeWAV(soundData);
    }
}