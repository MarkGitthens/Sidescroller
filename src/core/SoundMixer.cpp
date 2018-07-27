#include "SoundMixer.h"
#include <iostream>

namespace Vulture2D {
    SoundMixer* SoundMixer::instance = nullptr;

    SoundMixer& SoundMixer::getInstance() {
        if(!instance)
            instance = new SoundMixer();
        return *instance;
    }

    void SoundMixer::updateAudio() {
        if(SDL_GetQueuedAudioSize(deviceID) == 0) {
            if(!soundQueue.empty()) {
                for(int i = 0; i < soundQueue.size(); i++) {
                    playSound(soundQueue.at(i));
                    soundQueue.erase(soundQueue.begin() + i);
                }
            }
        }
    }

    void SoundMixer::playSound(Sound* sound) {
        format.freq = 48000;
        format.format = AUDIO_F32;
        format.channels = 2;
        format.samples = 4096;
        format.callback = nullptr;

        deviceID = SDL_OpenAudioDevice(NULL, 0, sound->getAudioInformation(), sound->getAudioInformation(), 0);

        if(deviceID == 0) {
            std::cout << "Failed to open audio device: " << SDL_GetError() << std::endl;
        } else {
            if(sound->loops())
                soundQueue.push_back(sound);
            SDL_QueueAudio(deviceID, sound->getSoundData(), sound->getLength());
            SDL_PauseAudioDevice(deviceID, 0);
        }
    }

    void SoundMixer::pausePlayback() {
        if(deviceID != 0)
            SDL_PauseAudioDevice(deviceID, 1);
    }

    void SoundMixer::stopPlayback() {
        if(deviceID) {
            SDL_ClearQueuedAudio(deviceID);
            SDL_CloseAudioDevice(deviceID);
        }
    }

    void SoundMixer::destroy() {
        stopPlayback();

        if(audioMix)
            delete audioMix;
        audioMix = nullptr;
    }
}