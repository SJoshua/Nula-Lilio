#ifndef SCENES_DIALOGUE_H
#define SCENES_DIALOGUE_H

#include <SDL.h>
#include <string>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"
#include "basic/Config.h"
#include "basic/Script.h"

#include "ui/Texture.h"

#include "scenes/Start.h"

class Dialogue: public Scene {
private:
	Script script;
	Texture background, character, text, name, delta;
	bool showCharacter, showName;
	int tick = 0;

public:
	Dialogue(std::string filename = "prologue.nls", int pos = 0);

	void process(void);

	void onKeyDown(SDL_Keycode code);

	void update(void);

	void render(void);
};

#endif
