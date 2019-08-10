#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <unordered_map>
#include <SDL.h>
#include <SDL_Image.h>
#include <SDL_ttf.h>
#include "Config.h"

extern SDL_Renderer *renderer;

class ResourceManager {
private:
	std::unordered_map <std::string, SDL_Texture*> pictures;
	std::unordered_map <std::string, SDL_Surface*> audios;
	std::unordered_map <std::string, std::unordered_map <int, TTF_Font*>> fonts;

	SDL_Texture* loadPicture(std::string path) {
		SDL_Surface *surface = IMG_Load(path.c_str());
		SDL_Texture *texture = nullptr;
		if (surface == nullptr) {
			std::cout << IMG_GetError() << std::endl;
		} else {
			texture = SDL_CreateTextureFromSurface(renderer, surface);
			if (texture == nullptr) {
				std::cout << SDL_GetError() << std::endl;
			}
			SDL_FreeSurface(surface);
		}		
		return texture;
	}

	TTF_Font* loadFont(std::string path, int size) {
		TTF_Font *font = TTF_OpenFont(path.c_str(), size);
		if (font == nullptr) {
			std::cout << TTF_GetError() << std::endl;
		} 
		return font;
	}

public:
    ResourceManager(void) {}

	TTF_Font* font(std::string filename, int size) {
		std::string path = "resource/fonts/" + filename;
		if (!fonts[filename].count(size)) {
			auto font = loadFont(path, size);
			if (font == nullptr) {
				std::cout << "[Failed] load font: " << path << std::endl;
			} else {
				fonts[filename][size] = font;
			}
		}
		return fonts[filename][size];
	}

	SDL_Texture* picture(std::string filename) {
		std::string path = "resource/pictures/" + filename;
		if (!pictures.count(filename)) {
			auto pic = loadPicture(path);
			if (pic == nullptr) {
				std::cout << "[Failed] load picture: " << path << std::endl;
			} else {
				pictures[filename] = pic;
			}
		}
		return pictures[filename];
	}

	SDL_Texture* text(std::string text, TTF_Font *font, SDL_Color color = {0, 0, 0}) {
		auto *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, WINDOW_WIDTH);
		auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		return texture;
	}

	void free(void) {
		for (auto e: pictures) {
			SDL_DestroyTexture(e.second);
		}
		for (auto e: audios) {
			// To-do
		}
		for (auto e: fonts) {
			for (auto s: e.second) {
				TTF_CloseFont(s.second);
			}
		}
	}
};

#endif