#ifndef BASIC_AUDIO_H
#define BASIC_AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <iostream>
#include <fstream>

#include "basic/Resource_Manager.h"
#include "basic/Config.h"

class Audio {
public:
	Audio (void);

	void PlayMusic(std::string filename);

	void PlayMusic(void);

	void PlayChunk(std::string filename);

	void PlayChunk(std::string filename, int loop_count);

	void StopMusic(void);

	void StopMusic(int late);

};

#endif 
