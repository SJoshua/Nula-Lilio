#ifndef BASIC_SAVEDATA_H
#define BASIC_SAVEDATA_H

#include <string>
#include <ctime>
#include <SDL.h>

class Savedata {
public:
	std::string tag, text;
	unsigned int pos;
	SDL_Texture *pic;
	time_t timestamp;

	Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture* pic, time_t timestamp);
};

#endif