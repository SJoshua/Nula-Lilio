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
#include "scenes/Save.h"
#include "scenes/Load.h"

class Dialogue: public Scene {
private:
	Script script;
	Texture background, character, text, name, delta;
	bool showCharacter, showName;
	int tick = 0;
	int speed = 0;
	int current = 5;
	// 0: auto
	// 1: skip
	// 2: save
	// 3: load
	// 4: title
	Button autoBtn, skipBtn, saveBtn, loadBtn, titleBtn;
	Audio bgm, se;

public:
	Dialogue(std::string filename = "prologue.nls", int pos = 0);

	void processScript(void);

	void processButtons(void);

	void onKeyDown(SDL_Keycode code);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
};

#endif
