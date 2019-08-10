#ifndef SCENES_LOAD_H
#define SCENES_LOAD_H

#include <SDL.h>
#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

class Load: public Scene {
private:

public:
	Load(void) {
	}

	void update(void) {

	}

	void render(void) {

	}
};

#endif