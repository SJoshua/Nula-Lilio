#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>

#include "basic/Config.h"

class ResourceManager {
private:
	std::unordered_map <std::string, SDL_Texture*> pictures;
	std::unordered_map <std::string, SDL_Surface*> audios;
	std::unordered_map <std::string, std::unordered_map <int, TTF_Font*>> fonts;

	SDL_Texture* loadPicture(std::string path);

	TTF_Font* loadFont(std::string path, int size);

public:
    ResourceManager(void);

	TTF_Font* font(std::string filename, int size);

	SDL_Texture* picture(std::string filename);

	SDL_Texture* text(std::string text, TTF_Font *font, SDL_Color color = {0, 0, 0});

	void free(void);

};

#endif
