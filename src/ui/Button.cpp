#include "ui/Button.h"

Button::Button(void) {
	normal = nullptr;
	active = nullptr;
	rect = { 0, 0, 0, 0 };
}

Button::Button(int x, int y, SDL_Texture *normal, SDL_Texture *active): normal(normal), active(active) {
    rect.x = x;
    rect.y = y;
	SDL_QueryTexture(normal, nullptr, nullptr, &rect.w, &rect.h);
}

SDL_Texture* Button::getNormal(void) {
    return normal;
}

SDL_Texture* Button::getActive(void) {
    return active;
}

SDL_Rect* Button::getRect(void) {
    return &rect;
}

bool Button::isInside(int px, int py) {
    return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
}