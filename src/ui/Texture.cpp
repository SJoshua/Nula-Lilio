#include "ui/Texture.h"

Texture::Texture(void) {
	texture = nullptr;
	rect = { 0, 0, 0, 0 };
}

Texture::Texture(int x, int y, SDL_Texture *texture): texture(texture) {
	rect.x = x;
	rect.y = y;
	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
}

void Texture::move(int dx, int dy) {
	rect.x += dx;
	rect.y += dy;
}

SDL_Texture* Texture::getTexture(void) {
	return texture;
}

SDL_Rect* Texture::getRect(void) {
	return &rect;
}

bool Texture::isInside(int px, int py) {
	return (rect.x <= px && px <= rect.x + rect.w && rect.y <= py && py <= rect.y + rect.h);
}