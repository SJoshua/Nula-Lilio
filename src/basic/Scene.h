#ifndef BASIC_SCENE_H
#define BASIC_SCENE_H

#include <SDL.h>

class Scene {
public:
	virtual void initFrame(void) {}
	virtual void onKeyDown(SDL_Keycode code) {}
	virtual void onMouseDown(int x, int y) {}
	virtual bool onMouseMove(int x, int y) {
		return false;
	}
	virtual void update(void) = 0;
	virtual void render(void) = 0;
};

#endif