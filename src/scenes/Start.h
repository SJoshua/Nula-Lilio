#ifndef SCENES_START_H
#define SCENES_START_H

#include "basic/Audio.h"
#include "basic/Config.h"
#include "basic/Resource_Manager.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"

#include "ui/Button.h"
#include "ui/Texture.h"

#include "scenes/Confirm.h"
#include "scenes/Dialogue.h"
#include "scenes/Load.h"

class Start: public Scene {
private:
	bool callback = false;
	int current = -1;
	// 0: Game Start
	// 1: Continue
	// 2: Exit
	Texture text;
	Button startBtn, continueBtn, exitBtn;

public:
	Start(void);

	void process(void);

	void onKeyDown(SDL_Keycode code);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
};

#endif