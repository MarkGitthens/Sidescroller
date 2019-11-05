#include "MusicPlayer.hpp"

void MusicPlayer::start() { channel = Game::getSoundMixer().playSound(&sound); }

void MusicPlayer::update() { /*STUB */}
void MusicPlayer::stop() { Game::getSoundMixer().stopChannel(channel); }