#ifndef UI_TEXTURE_H
#define UI_TEXTURE_H

#include <SDL.h>

class Texture {
private:
	SDL_Texture *texture;
	SDL_Rect rect;

public:
	Texture(void);

	Texture(int x, int y, SDL_Texture *texture);

	bool operator == (const Texture &p);

	bool operator != (const Texture &p);

	void move(int dx, int dy);

	void moveTo(int x, int y);

	void setAlpha(int value);

	SDL_Texture* getTexture(void);

	SDL_Rect* getRect(void);

	bool isInside(int px, int py);
};

#endif