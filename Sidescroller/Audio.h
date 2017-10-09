#pragma once
#include "Entity.h"
#include "InputHandler.h"
#include "EventHandler.h"
#include "SDL_mixer.h"
#include <iostream>
#include <string>
#include <mutex>

class Music : public Entity {
public:
    Music(char* name);
    ~Music();
    void update();
    void subscribeToEvents();
    void handleInput();
    bool load(char* file);
    void mute(int ret);
    void lowerVolume(int ret);
    void increaseVolume(int ret);
    std::string getMuteActionName() { return mMuteAction; }
    std::string getVolumeLowerActionName() { return mVolumeLowerAction; }
    std::string getVolumeHigherActionName() { return mVolumeHigherAction; }
private:
    const int VolumeChangeRate = 4; // Total range is [0,128]
    Mix_Music* mMixMusic;
    std::mutex mMusicMtx;
    std::string mMuteAction;
    std::string mVolumeLowerAction;
    std::string mVolumeHigherAction;
};

class AudioClip : public Entity {
public:
    AudioClip(char* name);
    ~AudioClip();
    void update();
    void subscribeToEvents();
    void handleInput();
    bool load(char* file);
    void play(int loops);
    void setVolumeLevel(int level);
    std::string getPlayActionName() { return mPlayAction; }
private:
    int mVolumeLevel;
    Mix_Chunk* mMixChunk;
    std::mutex mAudioMtx;
    std::string mPlayAction;
};