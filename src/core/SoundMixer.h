#pragma once
#include <SDL.h>
#include "Sound.h"
#include <vector>


namespace Vulture2D {
    using std::vector;
    class SoundMixer {
    public:
        static SoundMixer& getInstance();

        SoundMixer() : deviceID(0), audioMix(nullptr) {};

        void updateAudio();
        
        void playSound(Sound*);
        void pausePlayback();
        void stopPlayback();

        void destroy();
    private:
        static SoundMixer* instance;
        ~SoundMixer() {
            if(instance)
                delete instance;
            instance = nullptr;
        }

        SDL_AudioSpec format;
        SDL_AudioDeviceID deviceID;
        vector<Sound*> soundQueue;
        Uint8* audioMix;
    };
}