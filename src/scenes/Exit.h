#ifndef SCENES_EXIT_H
#define SCENES_EXIT_H

#include "basic/Config.h"
#include "basic/Resource_Manager.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"

#include "ui/Button.h"
#include "ui/Texture.h"

class Exit: public Scene {
private:
	int current = 2;
	Button yesBtn, noBtn;
	Texture notice;

public:
	Exit(void);

	void process(void);

	void onKeyDown(SDL_Keycode code);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
};

#endif