#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

class Button {
private:
	SDL_Texture *normal, *active;
	SDL_Rect rect;

public:
	Button(void);

	Button(int x, int y, SDL_Texture *normal, SDL_Texture *active);

	SDL_Texture* getNormal(void);

	SDL_Texture* getActive(void);

	SDL_Rect* getRect(void);

	bool isInside(int px, int py);
	
};

#endif