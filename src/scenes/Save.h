#ifndef SCENES_SAVE_H
#define SCENES_SAVE_H

#include <SDL.h>
#include "../Scene.h"
#include "../Scene_Manager.h"
#include "../Resource_Manager.h"

extern SceneManager scenes;
extern ResourceManager resources;
extern SDL_Renderer *renderer;

class Save: public Scene {
private:

public:
	Save (void) {
	}

	void update(void) {

	}

	void render(void) {
		
	}
};

#endif