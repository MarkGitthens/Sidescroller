#include "SoundMixer.h"

namespace Vulture2D {

    SoundMixer* SoundMixer::instance = nullptr;

    SoundMixer& SoundMixer::getInstance() {
        if(!instance) {
            instance = new SoundMixer();
        }
        return *instance;
    }

    void SoundMixer::init() {
        int flags = 0;
        int result = Mix_Init(flags);
        if(flags != result) {
            std::cout << "Couldn't load mixer: " << Mix_GetError() << std::endl;
        } else {
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
                std::cout << "Couldn't open audio: " << Mix_GetError() << std::endl;
            }
        }
    }

    //Updates all channels based from a reference entity
    void SoundMixer::updateSound() {
        for(size_t i = 0; i < playingSounds.size(); i++) {
            if(playingSounds.at(i)) {
                //Sound on that channel;
            }
        }
    }

    int SoundMixer::playSound(Sound* sound, int channel) {
        int loadedChannel = Mix_PlayChannel(channel, sound->getChunkData(), sound->loops() ? sound->loopCount() : 0);
        if(loadedChannel < 0) {
            std::cout << "Can't play sound: " << Mix_GetError() << std::endl;
        }

        sound->setChannel(loadedChannel);
        playingSounds.at(loadedChannel) = sound;

        return loadedChannel;
    }

    void SoundMixer::pauseChannel(int channel) {
        Mix_Pause(channel);
    }

    void SoundMixer::pauseAllChannels() {
        for(int i = 0; i < maxChannels; i++) {
            Mix_Pause(i);
        }
    }

    void SoundMixer::resumeChannel(int channel) {
        Mix_Resume(channel);
    }

    void SoundMixer::resumeAllChannels() {
        for(int i = 0; i < maxChannels; i++) {
            Mix_Resume(i);
        }
    }

    void SoundMixer::channel_finished(int channel) {
        playingSounds.at(channel)->setChannel(-1);
        playingSounds.at(channel) = nullptr;
    }
}
