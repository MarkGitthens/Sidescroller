#pragma once
#include <vector>
#include <iostream>
#include "Sound.h"

namespace Vulture2D {
    using std::vector;
    class SoundMixer {
    public:
        SoundMixer() : maxChannels(16), playingSounds(maxChannels){
            init();
            Mix_AllocateChannels(maxChannels);
        }
        SoundMixer(int numChannels): maxChannels(numChannels), playingSounds(maxChannels) {
            init();
            Mix_AllocateChannels(numChannels);
        }
        
        void init();
        static SoundMixer& getInstance();
        void updateSound();
        int playSound(Sound* sound, int channel = -1);
        void pauseChannel(int channel);
        void pauseAllChannels();
        void resumeChannel(int channel);
        void resumeAllChannels();

    private:
        static SoundMixer* instance;
        void channel_finished(int channel);
        ~SoundMixer() {
            if(instance)
                delete instance;
            instance = nullptr;

            Mix_Quit();
        }

        int maxChannels;
        //Sound* backgroundMusic;
        //vector since theoretically you can allocate more channels at any time
        vector<Sound*> playingSounds;
    };
}