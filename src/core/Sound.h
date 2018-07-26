#include <SDL.h>
#include <string>
#include <iostream>

namespace Vulture2D {
    using std::string;
    class Sound {
    public:
        Sound() : soundLength(0), soundData(nullptr) {}
        ~Sound();

        const SDL_AudioSpec& getAudioInformation();
        bool loadFromFile(string path);
        Uint32 getLength();
        void destroySound();
        void play(SDL_AudioDeviceID deviceID);
        void pause();
        void stop();

    private:
        SDL_AudioSpec soundInformation;
        Uint32 soundLength;
        Uint8* soundData;

    };
}