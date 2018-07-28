#pragma once
#include "Sound.h"

namespace Vulture2D {
    bool Sound::loops() {
        return doesLoop;
    }

    int Sound::loopCount() {
        return numLoops;
    }

    Mix_Chunk* Sound::getChunkData() {
        return chunk;
    }

    const Vector2D Sound::getPosition() {
        return *parentPosition;
    }

    void Sound::setChannel(int channel) {
        this->channel = channel;
    }

    int Sound::getChannel() {
        return channel;
    }
}