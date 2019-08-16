#ifndef SCENES_SAVE_H
#define SCENES_SAVE_H

#include <fstream>
#include <vector>
#include <SDL.h>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"

#include "ui/Texture.h"
#include "ui/Button.h"

#include "scenes/Dialogue.h"
#include "scenes/Saving.h"

struct loaddata {
	std::string tag;
	SDL_Texture *pic;
	int pos;
};

class Save : public Scene {
private:
	Texture background;
	std::vector <loaddata> data;
	int current = 10;
	/*
	0 return
	1 save_1
	2 save_2
	...
	9 save_9
	10 null
	*/
	Button returnBtn;
	Button Save_1Btn, Save_2Btn, Save_3Btn, Save_4Btn, Save_5Btn;
	Button Save_6Btn, Save_7Btn, Save_8Btn, Save_9Btn;

public:
	Save(void);

	void process(void);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);

};

#endif