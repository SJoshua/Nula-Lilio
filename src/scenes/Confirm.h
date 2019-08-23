#ifndef SCENES_CONFIRM_H
#define SCENES_CONFIRM_H

#include <string>

#include "basic/Config.h"
#include "basic/Resource_Manager.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"

#include "ui/Button.h"
#include "ui/Texture.h"

class Confirm: public Scene {
private:
	int current = 2;
	bool &ret;
	Button yesBtn, noBtn;
	Texture notice;

public:
	Confirm(bool &ret, std::string text);

	void process(void);

	void onKeyDown(SDL_Keycode code);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
};

#endif