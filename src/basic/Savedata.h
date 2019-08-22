#ifndef BASIC_SAVEDATA_H
#define BASIC_SAVEDATA_H

#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "basic/Resource_Manager.h"

class Savedata {
public:
	std::string tag, text;
	unsigned int pos;
	SDL_Texture *pic;
	time_t timestamp;

	Savedata(void);

	Savedata(std::string tag, std::string text, unsigned int pos, SDL_Texture *pic, time_t timestamp);

	std::string serialize(void);

	std::string getTime(void);

	void unserialize(std::string str);

	void write(int stock);

	void read(int stock);
};

#endif