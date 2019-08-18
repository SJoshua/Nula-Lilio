#include "basic/Audio.h"

extern ResourceManager resources;

Audio::Audio(void) {};

void Audio::PlayMusic(std::string filename)
{
	if ( ( Mix_PlayingMusic() == 1 ) | ( Mix_PausedMusic() == 1 ) ) {
		Mix_HaltMusic();
		Mix_PlayMusic(resources.music( filename ), -1);
	} else {
		Mix_PlayMusic(resources.music( filename ), -1);
	}
}

void Audio::PlayMusic(void)
{
	if ( Mix_PausedMusic() == 1 ) {
		Mix_ResumeMusic();
	}
}

void Audio::PlayChunk(std::string filename)
{
	Mix_PlayChannel(-1, resources.chunk( filename ), 0);	
}

void Audio::PlayChunk(std::string filename, int loop_count)
{
	Mix_PlayChannel(-1, resources.chunk( filename ), loop_count - 1);
}

void Audio::StopMusic(void)
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void Audio::StopMusic(int late)
{
	if (Mix_PlayingMusic() == 1)
	{
		for (int i = 128; i >= 0; i--)
		{
			Mix_VolumeMusic(i);
			SDL_Delay(late);
		}
		Mix_HaltMusic();
		Mix_VolumeMusic(128);
	}
}
