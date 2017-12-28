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

void Music::subscribeToEvents() {
    using std::placeholders::_1;
    EventHandler::getInstance().subscribeToEvent(mMuteAction, getName(), std::bind(&Music::mute, this, _1));
    EventHandler::getInstance().subscribeToEvent(mVolumeLowerAction, getName(), std::bind(&Music::lowerVolume, this, _1));
    EventHandler::getInstance().subscribeToEvent(mVolumeHigherAction, getName(), std::bind(&Music::increaseVolume, this, _1));
}

void Music::mute(int value) {
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

void Music::handleInput() {
    // Handle muting the music
    if (InputHandler::getInstance().actionPressTriggered(mMuteAction)) {
        mute(0);
    }
    else if (InputHandler::getInstance().actionPressTriggered(mVolumeLowerAction)) {
        lowerVolume(0);
    }
    else if (InputHandler::getInstance().actionPressTriggered(mVolumeHigherAction)) {
        increaseVolume(0);
    }
}

bool Music::load(char* file) {
    //Load music
    mMixMusic = Mix_LoadMUS(file);
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

void Music::lowerVolume(int ret) {
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

void Music::increaseVolume(int ret) {
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

AudioClip::AudioClip(char* name) {
    setName(name);
    mPlayAction = std::string(name) + "_play";
    // Set the default volume to 25%
    setVolumeLevel((int)(MIX_MAX_VOLUME * 0.25));
}

AudioClip::~AudioClip() {
    Mix_FreeChunk(mMixChunk);
    mMixChunk = nullptr;
}

void AudioClip::update() {
    handleInput();
}

void AudioClip::subscribeToEvents() {
    using std::placeholders::_1;
    EventHandler::getInstance().subscribeToEvent(mPlayAction, getName(), std::bind(&AudioClip::play, this, _1));
}

void AudioClip::handleInput() {
    // Play the sound clip
    if (InputHandler::getInstance().actionPressTriggered(mPlayAction)) {
        play(0);
    }
}

bool AudioClip::load(char* file) {
    //Load music
    mMixChunk = Mix_LoadWAV(file);
    if (mMixChunk == nullptr)
    {
        std::cerr << "Failed to load audio clip (" << file <<
            "SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    setVolumeLevel(mVolumeLevel);

    return true;
}

void AudioClip::play(int loops = 0) {
    Mix_PlayChannel(-1, mMixChunk, loops);
}

void AudioClip::setVolumeLevel(int level) {
    mVolumeLevel = level;
    Mix_VolumeChunk(mMixChunk, mVolumeLevel);
}