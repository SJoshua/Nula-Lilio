#ifndef SCENES_LOAD_H
#define SCENES_LOAD_H

#include <fstream>
#include <vector>
#include <SDL.h>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"

#include "ui/Texture.h"
#include "ui/Button.h"

#include "scenes/Start.h"
#include "scenes/Loading.h"

struct savedata {
	std::string tag;
	SDL_Texture *pic;
	int pos;
};

class Load: public Scene {
private:
	Texture background;
	std::vector <savedata> data;
	int current = 10;
	/*
	0 return
	1 load_1
	2 load_2
	...
	9 load_9
	10 null
	*/
	Button returnBtn;
	Button Load_1Btn, Load_2Btn, Load_3Btn, Load_4Btn, Load_5Btn;
	Button Load_6Btn, Load_7Btn, Load_8Btn, Load_9Btn;

public:
	Load(void);

	void process(void);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
	
};

#endif