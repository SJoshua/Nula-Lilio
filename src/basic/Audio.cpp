#include "basic/Audio.h"

extern ResourceManager resources;

Audio::Audio(void) {};

void Audio::playMusic(Mix_Music *music) {
	if ((Mix_PlayingMusic() == 1) | (Mix_PausedMusic() == 1)) {
		stopMusic();
	}
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(50);
}

void Audio::stopMusic(void) {
	if (Mix_PlayingMusic() == 1) {
		Mix_HaltMusic();
	}
}

void Audio::playSound(Mix_Chunk *chunk, int channel) {
	Mix_PlayChannel(channel, chunk, 0);
}

void Audio::stopSound(int channel) {
	Mix_HaltChannel(channel);
}

bool Audio::isPlayingSound(int channel) {
	return Mix_Playing(channel);
}
