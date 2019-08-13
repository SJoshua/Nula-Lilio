#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <deque>
#include <SDL.h>

#include "basic/Scene.h"

extern bool running;

class SceneManager {
private:
	std::deque <Scene*> list;

public:
	SceneManager(void);

	void push(Scene *scene);

	void pop(void);
	
	Scene* top(void);

	void jump(Scene *scene);

	void initFrame(void);

	void handle(SDL_Event &e);

	void update(void);

	void render(void);

};

#endif
