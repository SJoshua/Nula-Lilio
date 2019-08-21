#ifndef SCENES_SAVE_H
#define SCENES_SAVE_H

#include <fstream>
#include <vector>
#include <SDL.h>

#include "basic/Savedata.h"
#include "basic/Scene.h"
#include "basic/Scene_Manager.h"
#include "basic/Resource_Manager.h"

#include "ui/Texture.h"
#include "ui/Button.h"

#include "scenes/Dialogue.h"
#include "scenes/Saving.h"

class Save : public Scene {
private:
	Texture background;
	std::vector <Savedata> data;
	std::vector <Button> buttons;
	Savedata state;
	int current = 10;
	Button backBtn;

public:
	Save(Savedata data);

	void process(void);

	bool onMouseMove(int x, int y);

	void onMouseDown(int x, int y);

	void update(void);

	void render(void);

};

#endif