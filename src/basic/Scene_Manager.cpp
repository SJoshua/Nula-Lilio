#include "basic/Scene_Manager.h"
#include <iostream>

SceneManager::SceneManager(void) {
}

void SceneManager::push(Scene *scene) {
	list.push_back(scene);
}

void SceneManager::pop(void) {
	list.pop_back();
}

Scene* SceneManager::top(void) {
	return list.back();
}

void SceneManager::jump(Scene *scene) {
	pop();
	push(scene);
}

void SceneManager::initFrame(void) {
	for (auto s: list) {
		s->initFrame();
	}
}

void SceneManager::handle(SDL_Event &e) {
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

void SceneManager::update(void) {
	for (auto s: list) {
		s->update();
	}
}

void SceneManager::render(void) {
	for (auto s: list) {
		s->render();
	}
}
