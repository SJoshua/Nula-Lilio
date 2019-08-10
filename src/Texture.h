#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

class Texture {
private:
	SDL_Texture *texture;
	SDL_Rect rect;
public:
	Texture(void) {}
	Texture(int x, int y, SDL_Texture *texture): texture(texture) {
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	}
	void move(int dx, int dy) {
		rect.x += dx;
		rect.y += dy;
	}
	SDL_Texture* getTexture(void) {
		return texture;
	}
	SDL_Rect* getRect(void) {
		return &rect;
	}
	bool isInside(int px, int py) {
		return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
	}
};

#endif