#ifndef BASIC_AUDIO_H
#define BASIC_AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <fstream>
#include <iostream>

#include "basic/Config.h"
#include "basic/Resource_Manager.h"

class Audio {
public:
	Audio(void);

	void playMusic(Mix_Music *music);

	void stopMusic(void);

	void playSound(Mix_Chunk *chunk, int channel = -1);

	void stopSound(int channel = -1);
};

#endif
