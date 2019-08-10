#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <deque>

extern bool running;

class SceneManager {
private:
	std::deque <Scene*> list;

public:
    SceneManager(void) {}

	void push(Scene *scene) {
		list.push_back(scene);
	}

	void pop(void) {
		list.pop_back();
	}
	
	Scene* top(void) {
		return list.back();
	}

	void jump(Scene* scene) {
		Scene *s = top();
		pop();
		push(scene);
		delete s;		
	}

	void initFrame(void) {
		for (auto s: list) {
			s->initFrame();
		}
	}

	void handle(SDL_Event &e) {
		for (auto s: list) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_KEYDOWN) {
				top()->onKeyDown(e.key.keysym.sym);
			} else if (e.type == SDL_MOUSEMOTION) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				top()->onMouseMove(x, y);
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				top()->onMouseDown(x, y);
			} else {
				// To-do
			}
		}
	}

	void update(void) {
		for (auto s: list) {
			s->update();
		}
	}

	void render(void) {
		for (auto s: list) {
			s->render();
		}
	}
};

#endif