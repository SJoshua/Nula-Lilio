#ifndef SCENES_LOAD_H
#define SCENES_LOAD_H

#include <SDL.h>
#include <fstream>
#include <vector>

#include "basic/Resource_Manager.h"
#include "basic/Savedata.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"

#include "ui/Button.h"
#include "ui/Texture.h"

#include "scenes/Loading.h"
#include "scenes/Start.h"

class Load: public Scene {
private:
	Texture background, title, loadLabel;
	std::vector <Savedata> data;
	std::vector <Button> buttons;
	int current = 10;
	Button backBtn;

public:
	Load(void);

	void process(void);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);
};


#endif