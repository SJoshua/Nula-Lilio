#ifndef BASIC_RESOURCE_MANAGER_H
#define BASIC_RESOURCE_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "basic/Config.h"

class ResourceManager {
private:
	std::unordered_map <std::string, SDL_Texture*> pictures;
	std::unordered_map <std::string, Mix_Chunk*> chunks;
	std::unordered_map <std::string, Mix_Music*> musics;
	std::unordered_map <std::string, std::unordered_map <int, TTF_Font*>> fonts;

	SDL_Texture* loadPicture(std::string path);

	TTF_Font* loadFont(std::string path, int size);

	Mix_Chunk* loadChunk(std::string path);

	Mix_Music* loadMusic(std::string path);

public:
	ResourceManager(void);

	TTF_Font* font(std::string filename, int size);
	
	SDL_Texture* picture(std::string filename, bool force = false);

	Mix_Chunk* chunk(std::string filename);

	Mix_Music* music(std::string filename);

	SDL_Texture* text(std::string text, TTF_Font *font, SDL_Color color = {0, 0, 0});

	void init(void);

	void free(void);

};

#endif
