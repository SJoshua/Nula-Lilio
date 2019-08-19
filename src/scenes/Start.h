#ifndef SCENES_START_H
#define SCENES_START_H

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"
#include "basic/Config.h"
#include "basic/Audio.h"

#include "ui/Texture.h"
#include "ui/Button.h"

#include "scenes/Dialogue.h"
#include "scenes/Exit.h"
#include "scenes/Load.h"

class Start: public Scene {
private:
	int current = 4; 
	// 0: Game Start
	// 1: Continue
	// 2: Config
	// 3: Exit
	Texture text;
	Button startBtn, continueBtn, configBtn, exitBtn;
	Audio bgm,se;

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