#pragma once
#include "Entity.h"
#include "InputHandler.h"
#include "SDL_mixer.h"
#include <iostream>
#include <string>
#include <mutex>

class Music : public Entity {
public:
    Music(char* name);
    ~Music();
    void update();
    void handleInput();
    bool load(std::string file);
    void lowerVolume();
    void increaseVolume();
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