#include "Sound.h"

namespace Vulture2D {
    const SDL_AudioSpec& Sound::getAudioInformation() {
        return soundInformation;
    }

    bool Sound::loadFromFile(string path) {
        bool loaded = true;
        if(SDL_LoadWAV(path.c_str(), &soundInformation, &soundData, &soundLength) == NULL)
            loaded = false;

        soundInformation.callback = NULL;
        soundInformation.userdata = NULL;
        return  loaded;
    }

    Uint32 Sound::getLength() {
        return soundLength;
    }

    void Sound::destroySound() {
        SDL_FreeWAV(soundData);
    }

    void Sound::play(SDL_AudioDeviceID deviceID) {

    }

    void Sound::pause() {

    }

    void Sound::stop() {

    }
}