#include "Audio.h"

Music::Music(char* name) {
    setName(name);
    mMuteAction = std::string(name) + "_mute";
    mVolumeLowerAction = std::string(name) + "_volume_lower";
    mVolumeHigherAction = std::string(name) + "_volume_higher";
}

Music::~Music() {
    Mix_FreeMusic(mMixMusic);
    mMixMusic = nullptr;
}

void Music::update() {
    handleInput();
}

void Music::handleInput() {
    // Handle muting the music
    if (InputHandler::getInstance().actionPressTriggered(mMuteAction)) {
        if (mMusicMtx.try_lock()) {
            // If there is no music playing
            if (Mix_PlayingMusic() == 0) {
                Mix_PlayMusic(mMixMusic, -1);
            }
            // Music is already playing
            else {
                // If the music is paused
                if (Mix_PausedMusic() == 1)
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                // If the music is playing
                else
                {
                    // Pause the music
                    Mix_PauseMusic();
                }
            }
            //std::this_thread::sleep_for(std::chrono::milliseconds(200));
            mMusicMtx.unlock();
        }
    }
    else if (InputHandler::getInstance().actionPressTriggered(mVolumeLowerAction)) {
        if (mMusicMtx.try_lock()) {
            int volume_level = Mix_VolumeMusic(-1);
            if (volume_level >= VolumeChangeRate) {
                Mix_VolumeMusic(volume_level - VolumeChangeRate);
            }
            else {
                Mix_VolumeMusic(0);
            }
            mMusicMtx.unlock();
        }
    }
    else if (InputHandler::getInstance().actionPressTriggered(mVolumeHigherAction)) {
        if (mMusicMtx.try_lock()) {
            int volume_level = Mix_VolumeMusic(-1);
            if (volume_level <= MIX_MAX_VOLUME - VolumeChangeRate) {
                Mix_VolumeMusic(volume_level + VolumeChangeRate);
            }
            else {
                Mix_VolumeMusic(MIX_MAX_VOLUME);
            }
            mMusicMtx.unlock();
        }
    }
}

bool Music::load(std::string file) {
    //Load music
    mMixMusic = Mix_LoadMUS("audio/beat.wav");
    if (mMixMusic == nullptr)
    {
        std::cerr << "Failed to load music (" << file <<
            "SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    // Set Volume to a low-ish value 25%
    Mix_VolumeMusic(MIX_MAX_VOLUME * 0.25);

    return true;
}

void Music::lowerVolume() {

}