#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL.h>

class Texture {
private:
	SDL_Texture *texture;
	SDL_Rect rect;

public:
	Texture(void);

	Texture(int x, int y, SDL_Texture *texture);

	void move(int dx, int dy);

	SDL_Texture* getTexture(void);

	SDL_Rect* getRect(void);

	bool isInside(int px, int py);
};

#endif