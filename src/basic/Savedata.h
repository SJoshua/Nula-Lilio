#ifndef BASIC_SAVEDATA_H
#define BASIC_SAVEDATA_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <SDL.h>

class Savedata {
public:
	std::string tag, text;
	unsigned int pos;
	SDL_Texture *pic;
	time_t timestamp;

	Savedata(void);

	Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture* pic, time_t timestamp);

	std::string Serialize(void);

	void Unserialize(std::string);

	void write(int stock);

	void read(int stock);
};

#endif