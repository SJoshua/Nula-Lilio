#ifndef BUTTON_H
#define BUTTON_H

#include <SDL.h>

class Button {
private:
	SDL_Texture *normal, *active;
	SDL_Rect rect;
public:
	Button(void) {}
	Button(int x, int y, SDL_Texture *normal, SDL_Texture *active): normal(normal), active(active) {
		rect.x = x;
		rect.y = y;
		SDL_QueryTexture(normal, nullptr, nullptr, &rect.w, &rect.h);
	}
	SDL_Texture* getNormal(void) {
		return normal;
	}
	SDL_Texture* getActive(void) {
		return active;
	}
	SDL_Rect* getRect(void) {
		return &rect;
	}
	bool isInside(int px, int py) {
		return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
	}
};

#endif