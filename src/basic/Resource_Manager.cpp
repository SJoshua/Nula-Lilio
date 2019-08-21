#include "Resource_Manager.h"

extern SDL_Renderer *renderer;

ResourceManager::ResourceManager(void) {}

void ResourceManager::init(void) {
	SDL_Texture* black = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);
	SDL_Texture* white = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, WINDOW_WIDTH, WINDOW_HEIGHT);

	SDL_SetRenderTarget(renderer, black);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderTarget(renderer, white);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	pictures["white"] = white;
	pictures["black"] = black;

	SDL_SetRenderTarget(renderer, nullptr);
}

SDL_Texture* ResourceManager::loadPicture(std::string path) {
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

TTF_Font* ResourceManager::loadFont(std::string path, int size) {
	TTF_Font *font = TTF_OpenFont(path.c_str(), size);
	if (font == nullptr) {
		std::cout << TTF_GetError() << std::endl;
	} 
	return font;
}

Mix_Chunk* ResourceManager::loadChunk(std::string path) {
	Mix_Chunk *chunk = Mix_LoadWAV(path.c_str());
	if (chunk == nullptr) {
		std::cout << Mix_GetError() << std::endl;
	}
	return chunk;
}

Mix_Music* ResourceManager::loadMusic(std::string path) {
	Mix_Music *music = Mix_LoadMUS(path.c_str());
	if (music == nullptr) {
		std::cout << Mix_GetError() << std::endl;
	}
	return music;
}

TTF_Font* ResourceManager::font(std::string filename, int size) {
	std::string path = "./resource/fonts/" + filename;
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

SDL_Texture* ResourceManager::picture(std::string filename) {	
	std::string path = "./resource/pictures/" + filename;
	if (filename.empty()) {
		return nullptr;
	}
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

Mix_Chunk* ResourceManager::chunk(std::string filename) {
	std::string path = "./resource/chunks/" + filename;
	if (!chunks.count(filename)) {
		auto chu = loadChunk(path);
		if (chu == nullptr) {
			std::cout << "[Failed] load chunk: " << path << std::endl;
		} else {
			chunks[filename] = chu;
		}
	}
	return chunks[filename];
}

Mix_Music* ResourceManager::music(std::string filename) {
	std::string path = "./resource/musics/" + filename;
	if (!musics.count(filename)) {
		auto mus = loadMusic(path);
		if (mus == nullptr) {
			std::cout << "[Failed] load music: " << path << std::endl;
		}
		else {
			musics[filename] = mus;
		}
	}
	return musics[filename];
}

SDL_Texture* ResourceManager::text(std::string text, TTF_Font *font, SDL_Color color) {
	auto *surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, WINDOW_WIDTH);
	if (surface == nullptr) {
		std::cout << "[Failed] render text <" << text.c_str() << ">: " << TTF_GetError() << std::endl;
	}
	auto *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == nullptr) {
		std::cout << "[Failed] create texture: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surface);
	return texture;
}

void ResourceManager::free(void) {
	for (auto e: pictures) {
		SDL_DestroyTexture(e.second);
	}
	for (auto e: chunks) {
		Mix_FreeChunk(e.second);
	}
	for (auto e: musics) {
		Mix_FreeMusic(e.second);
	}
	for (auto e: fonts) {
		for (auto s: e.second) {
			TTF_CloseFont(s.second);
		}
	}
}
