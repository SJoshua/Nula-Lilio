#ifndef SCENES_DIALOGUE_H
#define SCENES_DIALOGUE_H

#include <SDL.h>
#include <ctime>
#include <string>
#include <utility>

#include "basic/Audio.h"
#include "basic/Config.h"
#include "basic/Resource_Manager.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Script.h"

#include "ui/Texture.h"

#include "scenes/Load.h"
#include "scenes/Save.h"
#include "scenes/Start.h"

class Dialogue: public Scene {
private:
	Script script;
	bool showCharacter, showName, callback = false;
	/* current: active button id
	 * 0: auto
	 * 1: skip
	 * 2: save
	 * 3: load
	 * 4: title
	 */
	int current = 5;
	int lastTick = 0;
	int tick = 0;
	int speed = 0;
	std::string bgm;
	std::vector<std::pair<Button, std::string>> select;
	std::vector<Position> bgPos, chPos;
	Texture background, character, text, name, delta;
	Button autoBtn, skipBtn, saveBtn, loadBtn, titleBtn;

	SDL_Texture* takeScreenshot(void);

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
