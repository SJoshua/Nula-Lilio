#ifndef SCENES_LOAD_H
#define SCENES_LOAD_H

#include <fstream>
#include <vector>
#include <SDL.h>

#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"

#include "ui/Texture.h"

struct savedata {
	std::string tag;
	SDL_Texture *pic;
	int pos;
};

class Load: public Scene {
private:
	Texture background;
	std::vector <savedata> data;
	int cur = 0;

public:
	Load(void);

	void update(void);

	void render(void);
	
};

#endif